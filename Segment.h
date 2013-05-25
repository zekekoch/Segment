//
//  Segment.h
//  DressTester
//
//  Created by Zeke Koch on 5/16/13.
//  Copyright (c) 2013 Zeke Koch. All rights reserved.
//

#ifndef DressTester_Segment_h
#define DressTester_Segment_h

#include <Arduino.h> //It is very important to remember this! note that if you are using Arduino 1.0 IDE, change "WProgram.h" to "Arduino.h"

static enum Strand
{
    RingTop,
    RingMiddle,
    RingBottom,
    VTop,
    VMiddle,
    VBottom,
    Vertical
} StrandIndex;


class Segment
{
    
private:
    static const int LightMapSize = 4;

    
    
public:

    int lightMap[LightMapSize];
    int length;

    Segment()
    {
        
    }
    
    Segment(String segment)
    {
        length = segment.length();
        int chunk = 0;
        int bit = 0;
        
        // i'm packing a string of one and zeros into four ints
        for(int light = 0;light<length;light++)
        {
            // crudely convert the current character to a digit (should be 1 or 0)
            // then set that bit in the current segment
            if (1 == segment[light] - '0')
            {
                lightMap[chunk] |= 1 << bit;
            }
            
            if (bit < 31)
            {
                bit++;
            }
            else
            {
                chunk++;
                bit = 0;
            }
        }
    }
    
    Segment(int s0, int s1, int s2, int s3, int segmentLength, Strand strand)
    {
        length = segmentLength;
        lightMap[0] = s0;
        lightMap[1] = s1;
        lightMap[2] = s2;
        lightMap[3] = s3;
    }
    
    ~Segment()
    {
        
    }
    
    Segment operator& (Segment param) {
        Segment temp = Segment();
        temp.length = (length > param.length) ? length : param.length;

        for (int i = 0;i<LightMapSize;i++)
        {
            temp.lightMap[i] = lightMap[i] & param.lightMap[i];
        }
        return (temp);
    }

    Segment operator| (Segment param) {
        Segment temp = Segment();
        temp.length = (length > param.length) ? length : param.length;
        
        
        for (int i = 0;i<LightMapSize;i++)
        {
            temp.lightMap[i] = lightMap[i] | param.lightMap[i];
        }
        return (temp);
    }
    
    int operator[] (const int index)
    {
        // i'm pulling the bits from an array of 32 bit ints
        // the int to pull is just the index / the size of an int
        // and the bit is then the remainder
        //
        // &'ing the int with a mask with just the appropriate bit set
        // to the appropriate checks to see if that's set
        
        if (lightMap[index/32] & (1 << index % 32))
            return 1;
        else
            return 0;
    }

    
    String toString ()
    {
        String s = "";
        for (int i = 0;i<LightMapSize;i++)
        {
            s+=("i");s+=(i);s+=(":");
            for (int bit = 0;bit<32;bit++)
            {
                s+= ((lightMap[i] >> bit) & 1);
            }
            s+= "\n";
        }
        return s;
    }
    
};


#endif
