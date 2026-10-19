// HeapCompat.cpp
//
// Serious Sam: The Second Encounter 1.07 was built with Microsoft Visual C++ 6.0
// and its Engine.dll allocates C++ objects from the heap of the system MSVCRT.DLL.
// This entity library is built with a modern MSVC toolset that has its own CRT
// heap. Memory is passed both ways between the engine and the entities (event
// copies, entity instances, template containers declared in engine headers...),
// so every C++ allocation made by this module is routed to the very same
// MSVCRT.DLL heap that the engine uses. That keeps new/delete pairs compatible
// no matter which side frees the memory.

#include <windows.h>
#include <new>

typedef void *(__cdecl *MallocFunc)(size_t);
typedef void (__cdecl *FreeFunc)(void *);

static MallocFunc _pfnMalloc = NULL;
static FreeFunc   _pfnFree   = NULL;

static void ResolveEngineHeap(void)
{
  HMODULE hCRT = GetModuleHandleA("msvcrt.dll");
  if (hCRT == NULL) {
    hCRT = LoadLibraryA("msvcrt.dll");
  }
  if (hCRT != NULL) {
    _pfnMalloc = (MallocFunc)GetProcAddress(hCRT, "malloc");
    _pfnFree   = (FreeFunc)  GetProcAddress(hCRT, "free");
  }
  // should never happen, but don't leave the module without an allocator
  if (_pfnMalloc == NULL || _pfnFree == NULL) {
    _pfnMalloc = &malloc;
    _pfnFree   = &free;
  }
}

static void *EngineHeapAlloc(size_t ctSize)
{
  if (_pfnMalloc == NULL) {
    ResolveEngineHeap();
  }
  return _pfnMalloc(ctSize == 0 ? 1 : ctSize);
}

static void EngineHeapFree(void *pMemory)
{
  if (pMemory == NULL) {
    return;
  }
  if (_pfnFree == NULL) {
    ResolveEngineHeap();
  }
  _pfnFree(pMemory);
}

void *operator new(size_t ctSize)
{
  void *pMemory = EngineHeapAlloc(ctSize);
  if (pMemory == NULL) {
    throw std::bad_alloc();
  }
  return pMemory;
}

void *operator new[](size_t ctSize)
{
  return operator new(ctSize);
}

void *operator new(size_t ctSize, const std::nothrow_t &) noexcept
{
  return EngineHeapAlloc(ctSize);
}

void *operator new[](size_t ctSize, const std::nothrow_t &) noexcept
{
  return EngineHeapAlloc(ctSize);
}

void operator delete(void *pMemory) noexcept                         { EngineHeapFree(pMemory); }
void operator delete[](void *pMemory) noexcept                       { EngineHeapFree(pMemory); }
void operator delete(void *pMemory, size_t) noexcept                 { EngineHeapFree(pMemory); }
void operator delete[](void *pMemory, size_t) noexcept               { EngineHeapFree(pMemory); }
void operator delete(void *pMemory, const std::nothrow_t &) noexcept   { EngineHeapFree(pMemory); }
void operator delete[](void *pMemory, const std::nothrow_t &) noexcept { EngineHeapFree(pMemory); }
