ksnip Docker container
======================

## Building the container yourself

```bash
# build
docker-compose build ksnip-desktop-build

# run
docker-compose up ksnip-desktop-build
```

## Running the pre-built container

```bash
docker-compose up ksnip-desktop-pre-built
```

## Using the container

- Visit <http://localhost:6080/>
- Run `qtcreator`
- Open project `/code/ksnip/CMakeLists.txt` (*File* menu)
- Press <kbd>Ctrl + B</kbd> to build and run ksnip


