#ifndef __TCAR_DXT_IMAGE_H__
#define __TCAR_DXT_IMAGE_H__

#include <array>
#include <cstring>
#include <cstdint>
#include <memory>
#include <vector>

#include "image.h"

namespace GenTC {

  union PhysicalDXTBlock {
    struct {
      uint16_t ep1;
      uint16_t ep2;
      uint32_t interpolation;
    };
    uint64_t dxt_block;
  };

  struct LogicalDXTBlock {
    uint8_t ep1[4];
    uint8_t ep2[4];
    uint8_t palette[4][4];
    uint8_t indices[16];

    LogicalDXTBlock &operator=(const LogicalDXTBlock &other) {
      memcpy(this, &other, sizeof(*this));
      return *this;
    }

    bool operator==(const LogicalDXTBlock &other) const {
      return memcmp(this, &other, sizeof(*this)) == 0;
    }
  };

  class DXTImage {
   public:
    DXTImage(const char *orig_fn, const char *cmp_fn);
    DXTImage(int width, int height, const uint8_t *rgb_data);
    DXTImage(int width, int height, const std::vector<uint8_t> &rgb_data,
             const std::vector<uint8_t> &dxt_data);
    DXTImage(int width, int height, const std::vector<uint8_t> &dxt_data);

    int Width() const { return _width;  }
    int Height() const { return _height;  }

    int BlocksWide() const { return _blocks_width;  }
    int BlocksHigh() const { return _blocks_height; }

    // RGBA image
    std::unique_ptr<RGBAImage> EndpointOneImage() const;
    std::unique_ptr<RGBAImage> EndpointTwoImage() const;
    std::unique_ptr<RGBAImage> DecompressedImage() const;

    // RGB 565 separated into bytes
    std::unique_ptr<RGB565Image> EndpointOneValues() const;
    std::unique_ptr<RGB565Image> EndpointTwoValues() const;

    static std::vector<uint8_t> TwoBitValuesToImage(const std::vector<uint8_t> &v);

    // Byte-wise image where each byte takes on of four values in [0, 255]
    std::vector<uint8_t> InterpolationImage() const {
      return std::move(TwoBitValuesToImage(InterpolationValues()));
    }

    // Original interpolation values
    std::vector<uint8_t> InterpolationValues() const;

    const std::vector<PhysicalDXTBlock> &PhysicalBlocks() const {
      return _physical_blocks;
    }

    const std::vector<LogicalDXTBlock> &LogicalBlocks() const {
      return _logical_blocks;
    }

    const LogicalDXTBlock &LogicalBlockAt(int x, int y) const {
      return _logical_blocks[BlockAt(x, y)];
    }

    const PhysicalDXTBlock &PhysicalBlockAt(int x, int y) const {
      return _physical_blocks[BlockAt(x, y)];
    }

    uint8_t InterpolationValueAt(int x, int y) const;
    void GetColorAt(int x, int y, uint8_t out[4]) const;

    std::vector<uint8_t> PredictIndices(int chunk_width, int chunk_height) const;
    std::vector<uint8_t> PredictIndicesLinearize(int chunk_width, int chunk_height) const;

    void ReassignIndices(int mse_threshold);

    std::vector<uint8_t> PaletteData() const;
    const std::vector<uint8_t> &IndexDiffs() const { return _indices; }

  private:
    uint32_t BlockAt(int x, int y) const {
      return (y / 4) * _blocks_width + (x / 4);
    }

    void Reencode();
    double PSNR() const;

    int _width;
    int _height;
    int _blocks_width;
    int _blocks_height;

    std::vector<PhysicalDXTBlock> _physical_blocks;
    std::vector<LogicalDXTBlock> _logical_blocks;

    std::vector<uint32_t> _index_palette;
    std::vector<uint8_t> _indices;

    std::vector<uint8_t> _src_img;
  };

}  // namespace GenTC

#endif
