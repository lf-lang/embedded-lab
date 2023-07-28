# Install Visual Studio Code

VS Code is an integrated development environment (IDE) provided by Microsoft. If you do not already have it, follow the [installation instructions](https://code.visualstudio.com/download).

Install the [cmake tools extension](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cmake-tools) to VS Code.

**FIXME**: .vscode/settings.json needs this:
```
    "cmake.environment": {
        "PICO_SDK_PATH":"../../lib/pico-sdk"
    },
```

**FIXME: Extensions**:

```
$ code --install-extension marus25.cortex-debug
$ code --install-extension ms-vscode.cmake-tools
$ code --install-extension ms-vscode.cpptools
```
Also need LF extension.