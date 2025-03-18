# filepath-analyzer
Takes a filepath as input and outputs various information about the path. Purely made for practice purposes.

## Usage
Compile using any C++ compiler. Then run `./main "FILE_PATH"` where `FILE_PATH` is any file path, e.g `./main "/usr/bin/ls"`


### Output
When run, the following informations are printed about the file path:
* Number of Total files
* Total directories
* Total size
* Largest file
* Most common extension

For example, running `./main "/usr/bin/"` on a Ubuntu system will output something similar to 
```
Total files: 952
Total directories: 1
Total size: 355974460 bytes
Largest file: /usr/bin/lto-dump-13 (29352592 bytes)
Most common extension: .12 (4 files)
```
