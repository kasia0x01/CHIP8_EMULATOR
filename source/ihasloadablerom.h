#ifndef IHASLOADABLEROM_H
#define IHASLOADABLEROM_H

#include <string>

class IHasLoadableROM
{
public:
    /*
     * Loads a ROM from the given file path. Returns true if successful, false otherwise.
     */
    virtual bool loadROM(const std::string& filePath) = 0;
};

#endif // IHASLOADABLEROM_H
