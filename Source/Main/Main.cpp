#ifdef SPY_EDITOR
#include "Editor.hpp"
#else
#include "Engine.hpp"
#endif

using namespace snack;

#ifdef SPY_EDITOR

int main(int argc, char* argv[])
{
    Editor editor;
    editor.SetUp();
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
