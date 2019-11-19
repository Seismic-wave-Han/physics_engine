#ifndef OBJECT_H
#define OBJECT_H

#include <vector>

class Object
{
public:
    Object();
private:
    std::vector<double> position = {0, 0};
    std::vector<double> velocity = {0, 0};
};

#endif // OBJECT_H
