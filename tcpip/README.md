# TCP/IP

## Generate compile_commands.json from CMake

Generate a `compile_commands.json` using CMake, run:

```bash
cmake -S . -B build -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
```

Once generated you can see this file inside the `/build` directory,
make sure to symlink it at root.

```bash
ln -s build/compile_commands.json compile_commands.json
```
