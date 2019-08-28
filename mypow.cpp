//
//  main.cpp
//  CplusTest
//
//  Created by koko Fan on 8/23/19.
//  Copyright © 2019 koko Fan. All rights reserved.
//

#include <iostream>

double mypow(double x, int n)
{
    if (n == 0)
        return 1;
    
    double result = mypow(x, n/2);
    
    if (n % 2 == 0)
        return result * result;
    else
        return x * result * result;
}

int main(int argc, char * argv[])
{
    double x = 2.5;
    int n = 5;
    double result = mypow(x, n);
    std::cout << result << std::endl;
}
