#ifndef __TCAR_CODEC_H__
#define __TCAR_CODEC_H__

#include <cstdint>
#include <vector>

#include "dxt_image.h"

namespace GenTC {

  // Compresses the DXT texture with the given width and height into a
  // GPU decompressible stream.
  std::vector<uint8_t> CompressDXT(const char *filename, const char *cmp_fn, int width, int height);

  DXTImage DecompressDXT(const std::vector<uint8_t> &cmp_data);

  void TestDXT(const char *filename, const char *cmp_fn, int width, int height);

}  // namespace GenTC

#endif  // __TCAR_CODEC_H__
