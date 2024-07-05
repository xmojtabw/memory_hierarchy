#include "memory.h"





QVector<QBitArray> generateAddresses(int locality, int Address_len, int records_len) {
    QVector<QBitArray> addresses;
    int localityBits = Address_len / 4; // Each locality corresponds to 1/4 of the address bits

    int randomDecimal = 0;
    for (int i = 0; i < localityBits; i++) {
        randomDecimal = (10*randomDecimal) + (rand() % 2);
    }
    // Calculate the number of bits for the locality
    // Generate addresses based on locality (if Address_len >= 4)
    for (int i = 0; i < records_len; i++) {
        int starting = randomDecimal;
        QBitArray address(Address_len, false); // Initialize with all zeros

        // Set the bits based on the locality (if Address_len >= 4)
        if (Address_len > 4) {
            switch (locality) {
            case 1:
                // Set the first localityBits bits to 1
                for (int j = 0; j < localityBits; ++j) {
                    address.setBit(j, (starting%10));
                    starting = starting/10;
                }
                for (int j = localityBits; j < Address_len; ++j) {
                    address.setBit(j, rand() % 2);
                }
                break;
            case 2:
                // Set the first half of the bits to 1
                for (int j = 0; j < Address_len / 2; ++j) {
                    address.setBit(j, starting%10);
                    starting = starting/10;
                }
                for (int j = Address_len / 2; j < Address_len; ++j) {
                    address.setBit(j, rand() % 2);
                }
                break;
            case 3:
                // Set the first 3/4 of the bits to 1
                for (int j = 0; j < 3 * localityBits; ++j) {
                    address.setBit(j, starting%10);
                    starting = starting/10;
                }
                for (int j = 3 * localityBits; j < Address_len; ++j) {
                    address.setBit(j, rand() % 2);
                }
                break;
            case 0:
                for (int j = 0; j < Address_len; ++j) {
                    address.setBit(j, rand() % 2);
                }

                break;
            }
        }
        else {
            for (int j = 0; j < Address_len; ++j) {
                address.setBit(j, rand() % 2);
            }
        }
        addresses.append(address);
    }

    return addresses;
}



Memory::Memory(int len,int tag_bits,int control_bits ,int block_size, mem_types mt,cache_pt cpt):
    len(len),x_len(pow(2,len)),block_size(block_size),tag_len(tag_bits),
    mt(mt),cpt(cpt),mem(pow(2,len)),ctrl_bits(pow(2,len))
{
    for(QBitArray & block : mem)
    {
        block.fill(false,tag_bits);
    }
    for (QBitArray & ctrl_bit : ctrl_bits)
    {
        ctrl_bit.fill(false,control_bits);
    }
    switch (cpt)
    {
    case lfu:
        {
            FUsed = new unsigned int [x_len];
            for(int i=0 ; i <x_len;i++ )
            {
                FUsed[i]=0;
            }
        }
        break;
    case lru:
        {
            TUsed = new unsigned int [x_len];
            for(int i=0 ; i <x_len;i++ )
            {
                TUsed[i]=0;
            }
        }
        break;
    case mru:
        {
            TUsed = new unsigned int [x_len];
            for(int i=0 ; i <x_len;i++ )
            {
                TUsed[i]=0;
            }
        }
        break;
    case fifo:
        {
            add_time = new unsigned int [x_len];
            for(int i=0 ; i <x_len;i++ )
            {
                add_time[i]=0;
            }
        }
        break;
    case rr:
        {

        }
        break;
    case map:
        {

        }
        break;
    default:
        break;
    }

}

bool Memory::getData(const QBitArray &address)
{
    if( mt == sram)
    {
        QBitArray index_bits = address;
        index_bits.resize(len);
        unsigned short index = index_bits.toUInt32(QSysInfo::BigEndian);
        QBitArray address_tag  = extractBits(len,len+tag_len,address);
        // qDebug() << "sram" <<index;
        if(ctrl_bits[index][0])
        { //record is valid
            //QBitArray record_tag = mem[index];
            if (address_tag==mem[index])
            {
                return true;
            }
        }
        // overwrite the record
        mem[index] = address_tag;
        ctrl_bits[index][0] = 1;
        return false ;

    }
    else if(mt==ttable)
    {
        QBitArray index_bits = address;
        index_bits.resize(len);
        unsigned short index = index_bits.toUInt32(QSysInfo::BigEndian);
        //qDebug() << index;
        if(ctrl_bits[index][0])
        {
            return true;
        }
        else
        {
            //overwirte
            ctrl_bits[index][0]=1;
            return false;
        }
    }
    else if (mt==tlb)
    {
        int i=-1;
        for(const QBitArray & tag : mem )
        {
            i++;
            if(!ctrl_bits[i][0])continue;//not valid

            if(tag == address)
            {
                if (cpt==lru or cpt==mru )
                {
                    query_count++;
                    TUsed[i] = query_count;
                }
                if(cpt==lfu)
                {
                    FUsed[i] ++;
                }
                return true;
            }

        }
        // return false;
        switch (cpt) {
        case lfu:
        {
            auto it = std::min_element(FUsed,FUsed+x_len);
            int index_of_min = it - FUsed;
            FUsed[index_of_min] =1;
            mem[index_of_min] = address;
            ctrl_bits[index_of_min][0] = true;
        }
            break;
        case lru:
        {
            auto it = std::min_element(TUsed,TUsed+x_len);
            int index_of_min = it - TUsed;
            query_count++;
            TUsed[index_of_min] =query_count;
            mem[index_of_min] = address;
            ctrl_bits[index_of_min][0] = true;
        }
        break;
        case mru:
        {
            auto it = std::max_element(TUsed,TUsed+x_len);
            int index_of_max = it - TUsed;
            query_count++;
            TUsed[index_of_max] =query_count;
            mem[index_of_max] = address;
            ctrl_bits[index_of_max][0] = true;
        }
        break;
        case fifo:
        {
            auto it = std::min_element(add_time,add_time+x_len);
            int index_of_min = it - add_time;
            add_count++;
            add_time[index_of_min] =add_count;
            mem[index_of_min] = address;
            ctrl_bits[index_of_min][0] = true;
        }
        break;
        case rr:
        {
            for(int i=0; i < x_len; i++ )
            {
                if(!ctrl_bits[i][0])
                {//free index
                    mem[i] = address;
                    ctrl_bits[i][0]=true;
                    return false;
                }
            }
            // no free index
            int random_index = rand()%x_len;
            mem[random_index] = address;
        }
        break;
        default:
            break;
        }
        return false;
    }
    else
    {
        //wrong policy
        return false;
    }


}

QBitArray Memory::extractBits(const int &start, const int &end,const QBitArray& address)
{
    int len = end - start;
    QBitArray out (len);
    for ( int i=0,j=start ; i< len; i++,j++)
    {
        out [i] = address[j];
    }
    return out;
}

QVector<QBitArray>  generateAddresses(int t_locality, int p_locality, int records_len, int addresslen)
{
    int packet_len = records_len/p_locality;
    QVector<QBitArray>  out ;
    for(int i=0 ; i<p_locality;i++ )
    {
        QVector<QBitArray>  packet =generateAddresses(t_locality,addresslen,packet_len);
        //qDebug() << packet;
        out.append(packet);
    }
    return out;
}

QString checkQ(query_detail qd)
{
   // if(qd.)
}
