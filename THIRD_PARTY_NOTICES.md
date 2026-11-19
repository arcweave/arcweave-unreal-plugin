# Third-party notices

The Unreal integration is covered by the repository's [MIT license](LICENSE). The bundled runtime libraries retain their own licenses.

| Dependency | Included files | License |
| --- | --- | --- |
| [Arcscript C++ interpreter](https://github.com/arcweave/arcscript-interpreters/tree/main/Cpp) | `Source/ThirdParty/ArcscriptTranspiler/Public/`, `ArcscriptTranspiler.dll`, `ArcscriptTranspiler.lib`, `libArcscriptTranspiler.dylib` | [BSD 3-Clause — Arcweave Inc.](Source/ThirdParty/ArcscriptTranspiler/licenses/Arcscript-LICENSE.txt) |
| [ANTLR 4 C++ runtime](https://github.com/antlr/antlr4/tree/8e6fd9147b3c9d36b60e2b6656871a55227efb1b/runtime/Cpp) | `antlr4-runtime.dll`, `libantlr4-runtime.dylib` | [BSD 3-Clause — The ANTLR Project](Source/ThirdParty/ArcscriptTranspiler/licenses/ANTLR4-LICENSE.txt) |

Runtime binaries are in `Source/ThirdParty/ArcscriptTranspiler/lib/`. The interpreter's [build configuration](https://github.com/arcweave/arcscript-interpreters/blob/a46ca79c958039120577d4bf354044da65eb0d28/Cpp/CMakeLists.txt) pins ANTLR to commit `8e6fd9147b3c9d36b60e2b6656871a55227efb1b`.

Keep both license texts with source or binary redistributions of these dependencies. Unreal Engine is supplied separately under Epic Games' terms.
