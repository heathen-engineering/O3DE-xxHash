# xxHash for O3DE

An [Open 3D Engine (O3DE)](https://o3de.org) gem that bundles [xxHash](https://xxhash.com) — an extremely fast non-cryptographic hash algorithm by **Yann Collet** — and exposes it to C++, Script Canvas, and Lua.

- **License (this gem):** Apache 2.0
- **License (xxHash library):** BSD 2-Clause — see [`Code/Source/ThirdParty/xxHash/LICENSE`](Code/Source/ThirdParty/xxHash/LICENSE)
- **Origin:** Heathen Group
- **Platforms:** Windows, Linux, Android, iOS

---

## Third-party attribution

This gem vendors the xxHash library unchanged (apart from a minor include-path adjustment required by the O3DE build system).

> **xxHash** — Extremely Fast Hash algorithm  
> Copyright (C) 2012–2023 Yann Collet  
> BSD 2-Clause License  
> Homepage: <https://xxhash.com>  
> Source repository: <https://github.com/Cyan4973/xxHash>

The full BSD 2-Clause license text is located at:
```
Gems/xxHash/Code/Source/ThirdParty/xxHash/LICENSE
```

---

## Become a GitHub Sponsor
[![Discord](https://img.shields.io/badge/Discord--1877F2?style=social&logo=discord)](https://discord.gg/6X3xrRc)
[![GitHub followers](https://img.shields.io/github/followers/heathen-engineering?style=social)](https://github.com/heathen-engineering?tab=followers)
Support Heathen by becoming a [GitHub Sponsor](https://github.com/sponsors/heathen-engineering). Sponsorship directly funds the development and maintenance of free tools like this, as well as our game development [Knowledge Base](https://heathen.group/) and community on [Discord](https://discord.gg/6X3xrRc).

Sponsors also get access to our private SourceRepo, which includes developer tools for O3DE, Unreal, Unity, and Godot.
Learn more or explore other ways to support @ [heathen.group/kb](https://heathen.group/kb/do-more/)

---

## What it does

xxHash provides three hash variants exposed through the `xxHashRequestBus` EBus:

| Function | Algorithm | Output | Notes |
|----------|-----------|--------|-------|
| `Hash32` | XXH32 | `AZ::u32` | Classic 32-bit; works on all platforms including 32-bit |
| `Hash64` | XXH64 | `AZ::u64` | Classic 64-bit; best on 64-bit systems |
| `Hash128` | XXH3\_128bits | `AZ::Uuid` | Modern 128-bit; fastest on current hardware |

All three accept an `AZStd::string` as input. `Hash32` and `Hash64` also accept an optional seed value. `Hash128` returns an `AZ::Uuid` — a first-class O3DE type that works in serialization, Script Canvas, Lua, and AZStd collections without any extra setup.

For high-throughput C++ code (e.g. raw byte buffers, streaming), you can also call the xxHash C API directly via `#include <xxHash/xxhash.h>`.

---

## Requirements

- O3DE engine **25.10.2** or compatible

---

## Setup

### 1. Add the gem to your O3DE project

Register the gem with the O3DE Project Manager, or add it directly to your project's `project.json`:

```json
"external_subdirectories": [
    "Gems/xxHash"
],
"gem_names": [
    "xxHash"
]
```

Then re-run CMake configuration so the build system picks up the new gem.

---

## Usage — C++

### Via the EBus (recommended for game code)

```cpp
#include <xxHash/xxHashBus.h>

// 32-bit hash with default seed
AZ::u32 hash32 = 0;
xxHash::xxHashRequestBus::BroadcastResult(hash32, &xxHash::xxHashRequests::Hash32, "my string", 0u);

// 64-bit hash with a custom seed
AZ::u64 hash64 = 0;
xxHash::xxHashRequestBus::BroadcastResult(hash64, &xxHash::xxHashRequests::Hash64, "my string", 12345ull);

// 128-bit hash returned as AZ::Uuid
AZ::Uuid hash128;
xxHash::xxHashRequestBus::BroadcastResult(hash128, &xxHash::xxHashRequests::Hash128, "my string");

AZStd::string asString = hash128.ToString<AZStd::string>();
```

### Via the AZ::Interface (lowest overhead, same process)

```cpp
#include <xxHash/xxHashBus.h>

if (auto* xxhash = xxHash::xxHashInterface::Get())
{
    AZ::u64 id = xxhash->Hash64("EntityName", 0);
    AZ::Uuid uid = xxhash->Hash128("AssetPath/MyAsset.png");
}
```

### Via the xxHash C API directly (raw performance)

Use this when you need to hash arbitrary byte buffers or use the streaming / secret-seed advanced APIs:

```cpp
#define XXH_STATIC_LINKING_ONLY   // optional: access advanced declarations
#include <xxHash/xxhash.h>

// Hash a raw buffer
const void* data   = myBuffer.data();
size_t      length = myBuffer.size();

XXH32_hash_t  h32  = XXH32(data, length, 0);
XXH64_hash_t  h64  = XXH64(data, length, 0);
XXH128_hash_t h128 = XXH3_128bits(data, length);
```

Any gem that lists `Gem::xxHash.API` (or `Gem::xxHash`) as a `BUILD_DEPENDENCY` has access to `<xxHash/xxhash.h>` automatically.

### CMake dependency

In your gem's `Code/CMakeLists.txt`, add `Gem::xxHash.API` to the appropriate target:

```cmake
BUILD_DEPENDENCIES
    PUBLIC
        Gem::xxHash.API
```

---

## Usage — Script Canvas

The `xxHashRequestBus` is fully reflected to the BehaviorContext. In Script Canvas, search the node palette for **xxHash** to find:

| Node | Inputs | Output |
|------|--------|--------|
| **Hash32** | `String`, `Seed (u32)` | `u32` |
| **Hash64** | `String`, `Seed (u64)` | `u64` |
| **Hash128** | `String` | `Uuid` |

All three nodes appear under the **xxHash** category and target the `xxHashRequestBus` broadcast address (no explicit address needed).

---

## Usage — Lua

```lua
local hash32  = xxHashRequestBus.Broadcast.Hash32("hello world", 0)
local hash64  = xxHashRequestBus.Broadcast.Hash64("hello world", 0)
local hash128 = xxHashRequestBus.Broadcast.Hash128("hello world")

-- AZ::Uuid has a built-in string conversion
Debug.Log(tostring(hash128))
```

---

## Public API reference

### `xxHashRequestBus` events

| Event | Signature | Description |
|-------|-----------|-------------|
| `Hash32` | `(string, u32 seed) → u32` | Classic 32-bit xxHash (XXH32) |
| `Hash64` | `(string, u64 seed) → u64` | Classic 64-bit xxHash (XXH64) |
| `Hash128` | `(string) → AZ::Uuid` | Modern 128-bit xxHash (XXH3\_128bits) |

### Public headers

| Header | Contents |
|--------|----------|
| `xxHash/xxHashBus.h` | EBus interface — include this for game/gem code |
| `xxHash/xxHashTypeIds.h` | AZ type ID constants |
| `xxHash/xxhash.h` | The full xxHash C library — include for raw buffer access |
