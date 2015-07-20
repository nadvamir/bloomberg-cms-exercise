#ifndef PARSERS_H
#define PARSERS_H

#include <iostream>
#include "include/Command.h"

CommandPtr parseMessage(std::istream& in);

#endif
