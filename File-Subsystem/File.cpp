#include "File.h"

File::File(const String& name) : name(name), creationDate(std::time(nullptr)), modificationDate(creationDate) {}