#pragma once

#if _DEBUG

#include <iostream>
#define SPY_LOG(msg) std::cout << "MSG:: " << msg << "\n"
#define SPY_LOG_ERROR(msg) std::cout << "ERROR:: " << msg << "\n"

#else

#define SPY_LOG(msg)
#define SPY_LOG_ERROR(msg)

#endif
