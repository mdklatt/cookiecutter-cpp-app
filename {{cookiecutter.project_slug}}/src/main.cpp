/**
 * Application entry point.
 */
int main(int argc, char* argv[])  {
    extern int cli(int, char* []);  // defined in cli.cpp
    return cli(argc, argv);
}
