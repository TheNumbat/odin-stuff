
# Dependencies

One of the goals of this project is to create a system without external libraries, but a few are used for non-essential tasks:

   - STB media libraries + picojson for processing assets in the asset builder tool
   - libclang for parsing C++ in the reflection-info metaprogram
   - SDL2 for implementing a secondary linux-compatible platform layer. The Win32 layer is implemented with only the Win32 APIs.
   - Dear ImGui to render immediate mode GUI components. Replaces custom immediate mode GUI system, for now.
