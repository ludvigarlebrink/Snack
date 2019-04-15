#ifdef SPY_EDITOR
#include "Editor.hpp"
#else
#include "Engine.hpp"
#endif

#include <string>
#include <vector>

using namespace snack;

#ifdef SPY_EDITOR

int main(int argc, char* argv[])
{
    std::vector<std::string> args;
    for (int32 i = 0; i < argc; ++i)
    {
        args.push_back(argv[i]);
    }

    Editor editor;
    editor.SetUp(args);
    editor.Run();
    editor.TearDown();
}

#else

int main(int argc, char* argv[])
{
    Engine engine;
    engine.SetUp();
    engine.Run();
    engine.TearDown();
}

#endif
