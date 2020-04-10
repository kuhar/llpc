/*
 ***********************************************************************************************************************
 *
 *  Copyright (c) 2017-2020 Advanced Micro Devices, Inc. All Rights Reserved.
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a copy
 *  of this software and associated documentation files (the "Software"), to deal
 *  in the Software without restriction, including without limitation the rights
 *  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *  copies of the Software, and to permit persons to whom the Software is
 *  furnished to do so, subject to the following conditions:
 *
 *  The above copyright notice and this permission notice shall be included in all
 *  copies or substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 *  SOFTWARE.
 *
 **********************************************************************************************************************/
/**
 ***********************************************************************************************************************
 * @file  llpcIntrinsDefs.h
 * @brief LLPC header file: contains various definitions used by LLPC AMDGPU-backend instrinics.
 ***********************************************************************************************************************
 */
#pragma once

#include <stdint.h>

namespace lgc
{

// Limits
static const unsigned MaxTessPatchVertices              = (1 << 6)  - 1;

static const unsigned MaxGeometryInvocations            = (1 << 7)  - 1;
static const unsigned MaxGeometryOutputVertices         = (1 << 11) - 1;

static const unsigned MaxComputeWorkgroupSize           = (1 << 16) - 1;

// Messages that can be generated by using s_sendmsg
static const unsigned GS_DONE = 3;            // GS wave is done
static const unsigned GS_ALLOC_REQ = 9;       // GS requests that parameter cache space be allocated
static const unsigned GS_CUT = 0x12;           // [3:0] = 2 (GS), [5:4] = 1 (cut)
static const unsigned GS_EMIT = 0x22;          // [3:0] = 2 (GS), [5:4] = 2 (emit)

static const unsigned GS_CUT_STREAM0 = 0x12;   // [3:0] = 2 (GS), [5:4] = 1 (cut), [9:8] = 0 (stream0)
static const unsigned GS_CUT_STREAM1 = 0x112;  // [3:0] = 2 (GS), [5:4] = 1 (cut), [9:8] = 1 (stream1)
static const unsigned GS_CUT_STREAM2 = 0x212;  // [3:0] = 2 (GS), [5:4] = 1 (cut), [9:8] = 2 (stream2)
static const unsigned GS_CUT_STREAM3 = 0x312;  // [3:0] = 2 (GS), [5:4] = 1 (cut), [9:8] = 3 (stream3)

static const unsigned GS_EMIT_STREAM0 = 0x22;  // [3:0] = 2 (GS), [5:4] = 2 (emit), [9:8] = 0 (stream0)
static const unsigned GS_EMIT_STREAM1 = 0x122; // [3:0] = 2 (GS), [5:4] = 2 (emit), [9:8] = 1 (stream1)
static const unsigned GS_EMIT_STREAM2 = 0x222; // [3:0] = 2 (GS), [5:4] = 2 (emit), [9:8] = 2 (stream2)
static const unsigned GS_EMIT_STREAM3 = 0x322; // [3:0] = 2 (GS), [5:4] = 2 (emit), [9:8] = 3 (stream3)

static const unsigned GS_EMIT_CUT_STREAM_ID_SHIFT = 0x8;    // Shift of STREAM_ID of the message GS_EMIT/GS_CUT
static const unsigned GS_EMIT_CUT_STREAM_ID_MASK = 0x300;   // Mask of STREAM_ID of the message GS_EMIT/GS_CUT

// Enumerates address spaces valid for AMD GPU (similar to LLVM header AMDGPU.h)
enum AddrSpace
{
    ADDR_SPACE_GLOBAL             = 1,          // Global memory
    ADDR_SPACE_LOCAL              = 3,          // Local memory
    ADDR_SPACE_CONST              = 4,          // Constant memory
    ADDR_SPACE_PRIVATE            = 5,          // Private memory
    ADDR_SPACE_CONST_32BIT        = 6,          // Constant 32-bit memory
    ADDR_SPACE_BUFFER_FAT_POINTER = 7,          // Buffer fat-pointer memory
};

// Enumerates the target for "export" instruction.
enum ExportTarget
{
    EXP_TARGET_MRT_0            = 0,            // MRT 0..7
    EXP_TARGET_Z                = 8,            // Z
    EXP_TARGET_PS_NULL          = 9,            // Null pixel shader export (no data)
    EXP_TARGET_POS_0            = 12,           // Position 0
    EXP_TARGET_POS_1            = 13,           // Position 1
    EXP_TARGET_POS_2            = 14,           // Position 2
    EXP_TARGET_POS_3            = 15,           // Position 3
    EXP_TARGET_POS_4            = 16,           // Position 4
    EXP_TARGET_PRIM             = 20,           // NGG primitive data (connectivity data)
    EXP_TARGET_PARAM_0          = 32,           // Param 0
                                                // Param 1..30
    EXP_TARGET_PARAM_31         = 63,           // Param 31
};

// Enumerates shader export format used for "export" instruction.
enum ExportFormat
{
    EXP_FORMAT_ZERO             = 0,            // ZERO
    EXP_FORMAT_32_R             = 1,            // 32_R
    EXP_FORMAT_32_GR            = 2,            // 32_GR
    EXP_FORMAT_32_AR            = 3,            // 32_AR
    EXP_FORMAT_FP16_ABGR        = 4,            // FP16_ABGR
    EXP_FORMAT_UNORM16_ABGR     = 5,            // UNORM16_ABGR
    EXP_FORMAT_SNORM16_ABGR     = 6,            // SNORM16_ABGR
    EXP_FORMAT_UINT16_ABGR      = 7,            // UINT16_ABGR
    EXP_FORMAT_SINT16_ABGR      = 8,            // SINT16_ABGR
    EXP_FORMAT_32_ABGR          = 9,            // 32_ABGR
};

// Enumerates data format of data in CB.
enum ColorDataFormat
{
    COLOR_DATA_FORMAT_INVALID                   = 0,            // Invalid
    COLOR_DATA_FORMAT_8                         = 1,            // 8
    COLOR_DATA_FORMAT_16                        = 2,            // 16
    COLOR_DATA_FORMAT_8_8                       = 3,            // 8_8
    COLOR_DATA_FORMAT_32                        = 4,            // 32
    COLOR_DATA_FORMAT_16_16                     = 5,            // 16_16
    COLOR_DATA_FORMAT_10_11_11                  = 6,            // 10_11_11
    COLOR_DATA_FORMAT_11_11_10                  = 7,            // 11_11_10
    COLOR_DATA_FORMAT_10_10_10_2                = 8,            // 10_10_10_2
    COLOR_DATA_FORMAT_2_10_10_10                = 9,            // 2_10_10_10
    COLOR_DATA_FORMAT_8_8_8_8                   = 10,           // 8_8_8_8
    COLOR_DATA_FORMAT_32_32                     = 11,           // 32_32
    COLOR_DATA_FORMAT_16_16_16_16               = 12,           // 16_16_16_16
    COLOR_DATA_FORMAT_32_32_32_32               = 14,           // 32_32_32_32
    COLOR_DATA_FORMAT_5_6_5                     = 16,           // 5_6_5
    COLOR_DATA_FORMAT_1_5_5_5                   = 17,           // 1_5_5_5
    COLOR_DATA_FORMAT_5_5_5_1                   = 18,           // 5_5_5_1
    COLOR_DATA_FORMAT_4_4_4_4                   = 19,           // 4_4_4_4
    COLOR_DATA_FORMAT_8_24                      = 20,           // 8_24
    COLOR_DATA_FORMAT_24_8                      = 21,           // 24_8
    COLOR_DATA_FORMAT_X24_8_32_FLOAT            = 22,           // X24_8_32_FLOAT
    COLOR_DATA_FORMAT_2_10_10_10_6E4            = 31,           // 2_10_10_10_6E4
};

// Enumerates numeric format of data in CB.
enum ColorNumFormat
{
    COLOR_NUM_FORMAT_UNORM                      = 0,            // UNORM
    COLOR_NUM_FORMAT_SNORM                      = 1,            // SNORM
    COLOR_NUM_FORMAT_USCALED                    = 2,            // USCALED
    COLOR_NUM_FORMAT_SSCALED                    = 3,            // SSCALED
    COLOR_NUM_FORMAT_UINT                       = 4,            // UINT
    COLOR_NUM_FORMAT_SINT                       = 5,            // SINT
    COLOR_NUM_FORMAT_SRGB                       = 6,            // SRGB
    COLOR_NUM_FORMAT_FLOAT                      = 7,            // FLOAT
};

// Enumrates CB component swap mode.
enum ColorSwap
{
    COLOR_SWAP_STD                              = 0,            // STD
    COLOR_SWAP_ALT                              = 1,            // ALT
    COLOR_SWAP_STD_REV                          = 2,            // STD_REV
    COLOR_SWAP_ALT_REV                          = 3,            // ALT_REV
};

// Enumerates parameter values used in "flat" interpolation (v_interp_mov).
enum InterpParam
{
    INTERP_PARAM_P10            = 0,            // P10
    INTERP_PARAM_P20            = 1,            // P20
    INTERP_PARAM_P0             = 2,            // P0
};

// Enumerates data format of data in memory buffer.
enum BufDataFmt
{
    BUF_DATA_FORMAT_INVALID                     = 0,            // Invalid
    BUF_DATA_FORMAT_8                           = 1,            // 8
    BUF_DATA_FORMAT_16                          = 2,            // 16
    BUF_DATA_FORMAT_8_8                         = 3,            // 8_8
    BUF_DATA_FORMAT_32                          = 4,            // 32
    BUF_DATA_FORMAT_16_16                       = 5,            // 16_16
    BUF_DATA_FORMAT_10_11_11                    = 6,            // 10_11_11
    BUF_DATA_FORMAT_11_11_10                    = 7,            // 11_11_10
    BUF_DATA_FORMAT_10_10_10_2                  = 8,            // 10_10_10_2
    BUF_DATA_FORMAT_2_10_10_10                  = 9,            // 2_10_10_10
    BUF_DATA_FORMAT_8_8_8_8                     = 10,           // 8_8_8_8
    BUF_DATA_FORMAT_32_32                       = 11,           // 32_32
    BUF_DATA_FORMAT_16_16_16_16                 = 12,           // 16_16_16_16
    BUF_DATA_FORMAT_32_32_32                    = 13,           // 32_32_32
    BUF_DATA_FORMAT_32_32_32_32                 = 14,           // 32_32_32_32
};

// Enumerates numeric format of data in memory buffer.
enum BufNumFmt
{
    BUF_NUM_FORMAT_UNORM                        = 0,            // Unorm
    BUF_NUM_FORMAT_SNORM                        = 1,            // Snorm
    BUF_NUM_FORMAT_USCALED                      = 2,            // Uscaled
    BUF_NUM_FORMAT_SSCALED                      = 3,            // Sscaled
    BUF_NUM_FORMAT_UINT                         = 4,            // Uint
    BUF_NUM_FORMAT_SINT                         = 5,            // Sint
    BUF_NUM_FORMAT_SNORM_OGL                    = 6,            // Snorm_ogl
    BUF_NUM_FORMAT_FLOAT                        = 7,            // Float
};

// Enumerates float round modes.
enum FloatRoundMode
{
    FP_ROUND_TO_NEAREST_EVEN                    = 0,            // RTE
    FP_ROUND_TO_POSITIVE_INF                    = 1,            // RTP
    FP_ROUND_TO_NEGATIVE_INF                    = 2,            // RTN
    FP_ROUND_TO_ZERO                            = 3,            // RTZ
};

// Enumerates float denormal modes.
enum FloatDenormMode
{
    FP_DENORM_FLUSH_IN_OUT                      = 0,            // Flush input/output denormals
    FP_DENORM_FLUSH_OUT                         = 1,            // Allow input denormals and flush output denormals
    FP_DENORM_FLUSH_IN                          = 2,            // Flush input denormals and allow output denormals
    FP_DENORM_FLUSH_NONE                        = 3,            // Allow input/output denormals
};

// Represents float modes for 16-bit/64-bit and 32-bit floating-point types.
union FloatMode
{
    struct
    {
        unsigned    fp32RoundMode       : 2;            // FP32 round mode
        unsigned    fp16fp64RoundMode   : 2;            // FP16/FP64 round mode
        unsigned    fp32DenormMode      : 2;            // FP32 denormal mode
        unsigned    fp16fp64DenormMode  : 2;            // FP16/FP64 denormal mode
    } bits;

    unsigned u32All;
};

enum BufFormat
{
    BUF_FORMAT_INVALID                          = 0x00000000,
    BUF_FORMAT_8_UNORM                          = 0x00000001,
    BUF_FORMAT_8_SNORM                          = 0x00000002,
    BUF_FORMAT_8_USCALED                        = 0x00000003,
    BUF_FORMAT_8_SSCALED                        = 0x00000004,
    BUF_FORMAT_8_UINT                           = 0x00000005,
    BUF_FORMAT_8_SINT                           = 0x00000006,
    BUF_FORMAT_16_UNORM                         = 0x00000007,
    BUF_FORMAT_16_SNORM                         = 0x00000008,
    BUF_FORMAT_16_USCALED                       = 0x00000009,
    BUF_FORMAT_16_SSCALED                       = 0x0000000A,
    BUF_FORMAT_16_UINT                          = 0x0000000B,
    BUF_FORMAT_16_SINT                          = 0x0000000C,
    BUF_FORMAT_16_FLOAT                         = 0x0000000D,
    BUF_FORMAT_8_8_UNORM                        = 0x0000000E,
    BUF_FORMAT_8_8_SNORM                        = 0x0000000F,
    BUF_FORMAT_8_8_USCALED                      = 0x00000010,
    BUF_FORMAT_8_8_SSCALED                      = 0x00000011,
    BUF_FORMAT_8_8_UINT                         = 0x00000012,
    BUF_FORMAT_8_8_SINT                         = 0x00000013,
    BUF_FORMAT_32_UINT                          = 0x00000014,
    BUF_FORMAT_32_SINT                          = 0x00000015,
    BUF_FORMAT_32_FLOAT                         = 0x00000016,
    BUF_FORMAT_16_16_UNORM                      = 0x00000017,
    BUF_FORMAT_16_16_SNORM                      = 0x00000018,
    BUF_FORMAT_16_16_USCALED                    = 0x00000019,
    BUF_FORMAT_16_16_SSCALED                    = 0x0000001A,
    BUF_FORMAT_16_16_UINT                       = 0x0000001B,
    BUF_FORMAT_16_16_SINT                       = 0x0000001C,
    BUF_FORMAT_16_16_FLOAT                      = 0x0000001D,
    BUF_FORMAT_10_11_11_UNORM                   = 0x0000001E,
    BUF_FORMAT_10_11_11_SNORM                   = 0x0000001F,
    BUF_FORMAT_10_11_11_USCALED                 = 0x00000020,
    BUF_FORMAT_10_11_11_SSCALED                 = 0x00000021,
    BUF_FORMAT_10_11_11_UINT                    = 0x00000022,
    BUF_FORMAT_10_11_11_SINT                    = 0x00000023,
    BUF_FORMAT_10_11_11_FLOAT                   = 0x00000024,
    BUF_FORMAT_11_11_10_UNORM                   = 0x00000025,
    BUF_FORMAT_11_11_10_SNORM                   = 0x00000026,
    BUF_FORMAT_11_11_10_USCALED                 = 0x00000027,
    BUF_FORMAT_11_11_10_SSCALED                 = 0x00000028,
    BUF_FORMAT_11_11_10_UINT                    = 0x00000029,
    BUF_FORMAT_11_11_10_SINT                    = 0x0000002A,
    BUF_FORMAT_11_11_10_FLOAT                   = 0x0000002B,
    BUF_FORMAT_10_10_10_2_UNORM                 = 0x0000002C,
    BUF_FORMAT_10_10_10_2_SNORM                 = 0x0000002D,
    BUF_FORMAT_10_10_10_2_USCALED               = 0x0000002E,
    BUF_FORMAT_10_10_10_2_SSCALED               = 0x0000002F,
    BUF_FORMAT_10_10_10_2_UINT                  = 0x00000030,
    BUF_FORMAT_10_10_10_2_SINT                  = 0x00000031,
    BUF_FORMAT_2_10_10_10_UNORM                 = 0x00000032,
    BUF_FORMAT_2_10_10_10_SNORM                 = 0x00000033,
    BUF_FORMAT_2_10_10_10_USCALED               = 0x00000034,
    BUF_FORMAT_2_10_10_10_SSCALED               = 0x00000035,
    BUF_FORMAT_2_10_10_10_UINT                  = 0x00000036,
    BUF_FORMAT_2_10_10_10_SINT                  = 0x00000037,
    BUF_FORMAT_8_8_8_8_UNORM                    = 0x00000038,
    BUF_FORMAT_8_8_8_8_SNORM                    = 0x00000039,
    BUF_FORMAT_8_8_8_8_USCALED                  = 0x0000003A,
    BUF_FORMAT_8_8_8_8_SSCALED                  = 0x0000003B,
    BUF_FORMAT_8_8_8_8_UINT                     = 0x0000003C,
    BUF_FORMAT_8_8_8_8_SINT                     = 0x0000003D,
    BUF_FORMAT_32_32_UINT                       = 0x0000003E,
    BUF_FORMAT_32_32_SINT                       = 0x0000003F,
    BUF_FORMAT_32_32_FLOAT                      = 0x00000040,
    BUF_FORMAT_16_16_16_16_UNORM                = 0x00000041,
    BUF_FORMAT_16_16_16_16_SNORM                = 0x00000042,
    BUF_FORMAT_16_16_16_16_USCALED              = 0x00000043,
    BUF_FORMAT_16_16_16_16_SSCALED              = 0x00000044,
    BUF_FORMAT_16_16_16_16_UINT                 = 0x00000045,
    BUF_FORMAT_16_16_16_16_SINT                 = 0x00000046,
    BUF_FORMAT_16_16_16_16_FLOAT                = 0x00000047,
    BUF_FORMAT_32_32_32_UINT                    = 0x00000048,
    BUF_FORMAT_32_32_32_SINT                    = 0x00000049,
    BUF_FORMAT_32_32_32_FLOAT                   = 0x0000004A,
    BUF_FORMAT_32_32_32_32_UINT                 = 0x0000004B,
    BUF_FORMAT_32_32_32_32_SINT                 = 0x0000004C,
    BUF_FORMAT_32_32_32_32_FLOAT                = 0x0000004D,
    BUF_FORMAT_RESERVED_78                      = 0x0000004E,
    BUF_FORMAT_RESERVED_79                      = 0x0000004F,
    BUF_FORMAT_RESERVED_80                      = 0x00000050,
    BUF_FORMAT_RESERVED_81                      = 0x00000051,
    BUF_FORMAT_RESERVED_82                      = 0x00000052,
    BUF_FORMAT_RESERVED_83                      = 0x00000053,
    BUF_FORMAT_RESERVED_84                      = 0x00000054,
    BUF_FORMAT_RESERVED_85                      = 0x00000055,
    BUF_FORMAT_RESERVED_86                      = 0x00000056,
    BUF_FORMAT_RESERVED_87                      = 0x00000057,
    BUF_FORMAT_RESERVED_88                      = 0x00000058,
    BUF_FORMAT_RESERVED_89                      = 0x00000059,
    BUF_FORMAT_RESERVED_90                      = 0x0000005A,
    BUF_FORMAT_RESERVED_91                      = 0x0000005B,
    BUF_FORMAT_RESERVED_92                      = 0x0000005C,
    BUF_FORMAT_RESERVED_93                      = 0x0000005D,
    BUF_FORMAT_RESERVED_94                      = 0x0000005E,
    BUF_FORMAT_RESERVED_95                      = 0x0000005F,
    BUF_FORMAT_RESERVED_96                      = 0x00000060,
    BUF_FORMAT_RESERVED_97                      = 0x00000061,
    BUF_FORMAT_RESERVED_98                      = 0x00000062,
    BUF_FORMAT_RESERVED_99                      = 0x00000063,
    BUF_FORMAT_RESERVED_100                     = 0x00000064,
    BUF_FORMAT_RESERVED_101                     = 0x00000065,
    BUF_FORMAT_RESERVED_102                     = 0x00000066,
    BUF_FORMAT_RESERVED_103                     = 0x00000067,
    BUF_FORMAT_RESERVED_104                     = 0x00000068,
    BUF_FORMAT_RESERVED_105                     = 0x00000069,
    BUF_FORMAT_RESERVED_106                     = 0x0000006A,
    BUF_FORMAT_RESERVED_107                     = 0x0000006B,
    BUF_FORMAT_RESERVED_108                     = 0x0000006C,
    BUF_FORMAT_RESERVED_109                     = 0x0000006D,
    BUF_FORMAT_RESERVED_110                     = 0x0000006E,
    BUF_FORMAT_RESERVED_111                     = 0x0000006F,
    BUF_FORMAT_RESERVED_112                     = 0x00000070,
    BUF_FORMAT_RESERVED_113                     = 0x00000071,
    BUF_FORMAT_RESERVED_114                     = 0x00000072,
    BUF_FORMAT_RESERVED_115                     = 0x00000073,
    BUF_FORMAT_RESERVED_116                     = 0x00000074,
    BUF_FORMAT_RESERVED_117                     = 0x00000075,
    BUF_FORMAT_RESERVED_118                     = 0x00000076,
    BUF_FORMAT_RESERVED_119                     = 0x00000077,
    BUF_FORMAT_RESERVED_120                     = 0x00000078,
    BUF_FORMAT_RESERVED_121                     = 0x00000079,
    BUF_FORMAT_RESERVED_122                     = 0x0000007A,
    BUF_FORMAT_RESERVED_123                     = 0x0000007B,
    BUF_FORMAT_RESERVED_124                     = 0x0000007C,
    BUF_FORMAT_RESERVED_125                     = 0x0000007D,
    BUF_FORMAT_RESERVED_126                     = 0x0000007E,
    BUF_FORMAT_RESERVED_127                     = 0x0000007F,
};

// Enumerates destination selection of data in memory buffer.
enum BufDstSel
{
    BUF_DST_SEL_0 = 0,    // SEL_0 (0.0)
    BUF_DST_SEL_1 = 1,    // SEL_1 (1.0)
    BUF_DST_SEL_X = 4,    // SEL_X (X)
    BUF_DST_SEL_Y = 5,    // SEL_Y (Y)
    BUF_DST_SEL_Z = 6,    // SEL_Z (Z)
    BUF_DST_SEL_W = 7,    // SEL_W (W)
};

// Bits in mask supplied to v_cmp_class
enum CmpClass
{
    SignalingNaN = 1,
    QuietNaN = 2,
    NegativeInfinity = 4,
    NegativeNormal = 8,
    NegativeSubnormal = 0x10,
    NegativeZero = 0x20,
    PositiveZero = 0x40,
    PositiveSubnormal = 0x80,
    PositiveNormal = 0x100,
    PositiveInfinity = 0x200
};

// Represents register fields of SPI_PS_INPUT_ADDR.
union SpiPsInputAddr
{
    struct
    {
        unsigned    PERSP_SAMPLE_ENA        : 1;
        unsigned    PERSP_CENTER_ENA        : 1;
        unsigned    PERSP_CENTROID_ENA      : 1;
        unsigned    PERSP_PULL_MODEL_ENA    : 1;
        unsigned    LINEAR_SAMPLE_ENA       : 1;
        unsigned    LINEAR_CENTER_ENA       : 1;
        unsigned    LINEAR_CENTROID_ENA     : 1;
        unsigned    LINE_STIPPLE_TEX_ENA    : 1;
        unsigned    POS_X_FLOAT_ENA         : 1;
        unsigned    POS_Y_FLOAT_ENA         : 1;
        unsigned    POS_Z_FLOAT_ENA         : 1;
        unsigned    POS_W_FLOAT_ENA         : 1;
        unsigned    FRONT_FACE_ENA          : 1;
        unsigned    ANCILLARY_ENA           : 1;
        unsigned    SAMPLE_COVERAGE_ENA     : 1;
        unsigned    POS_FIXED_PT_ENA        : 1;
        unsigned                            : 16;
    } bits;

    unsigned u32All;
};

// Represents the first DWORD of buffer descriptor SQ_BUF_RSRC_WORD0.
union SqBufRsrcWord0
{
    struct
    {
        unsigned    BASE_ADDRESS : 32;
    } bits;

    unsigned u32All;
};

// Represents the second DWORD of buffer descriptor SQ_BUF_RSRC_WORD1.
union SqBufRsrcWord1
{
    struct
    {
        unsigned    BASE_ADDRESS_HI : 16;
        unsigned    STRIDE          : 14;
        unsigned    CACHE_SWIZZLE   : 1;
        unsigned    SWIZZLE_ENABLE  : 1;
    } bits;

    unsigned	u32All;
};

// Represents the third DWORD of buffer descriptor SQ_BUF_RSRC_WORD2.
union SqBufRsrcWord2
{
    struct
    {
        unsigned    NUM_RECORDS : 32;
    } bits;

    unsigned u32All;
};

// Represents the forth DWORD of buffer descriptor SQ_BUF_RSRC_WORD3.
union SqBufRsrcWord3
{
    struct
    {
        unsigned    DST_SEL_X       : 3;
        unsigned    DST_SEL_Y       : 3;
        unsigned    DST_SEL_Z       : 3;
        unsigned    DST_SEL_W       : 3;
        unsigned                    : 9;
        unsigned    INDEX_STRIDE    : 2;
        unsigned    ADD_TID_ENABLE  : 1;
        unsigned                    : 6;
        unsigned    TYPE            : 2;
    } bits;

    struct
    {
        unsigned                    : 12;
        unsigned    NUM_FORMAT      : 3;
        unsigned    DATA_FORMAT     : 4;
        unsigned    ELEMENT_SIZE    : 2;
        unsigned                    : 3;
        unsigned    ATC             : 1;
        unsigned    HASH_ENABLE     : 1;
        unsigned    HEAP            : 1;
        unsigned    MTYPE           : 3;
        unsigned                    : 2;
    } gfx6;

    struct
    {
        unsigned                    : 12;
        unsigned    FORMAT          : 7;
        unsigned                    : 5;
        unsigned    RESOURCE_LEVEL  : 1;
        unsigned                    : 3;
        unsigned    OOB_SELECT      : 2;
        unsigned                    : 2;
    } gfx10;

    unsigned u32All;
};

// Represent register fields of PA_SU_SC_MODE_CNTL
union PaSuScModeCntl
{
    struct
    {
        unsigned CULL_FRONT                                 : 1;
        unsigned CULL_BACK                                  : 1;
        unsigned FACE                                       : 1;
        unsigned POLY_MODE                                  : 2;
        unsigned POLYMODE_FRONT_PTYPE                       : 3;
        unsigned POLYMODE_BACK_PTYPE                        : 3;
        unsigned POLY_OFFSET_FRONT_ENABLE                   : 1;
        unsigned POLY_OFFSET_BACK_ENABLE                    : 1;
        unsigned POLY_OFFSET_PARA_ENABLE                    : 1;
        unsigned                                            : 2;
        unsigned VTX_WINDOW_OFFSET_ENABLE                   : 1;
        unsigned                                            : 2;
        unsigned PROVOKING_VTX_LAST                         : 1;
        unsigned PERSP_CORR_DIS                             : 1;
        unsigned MULTI_PRIM_IB_ENA                          : 1;
        unsigned                                            : 10;
    } bits;

    struct
    {
        unsigned                                            : 22;
        unsigned RIGHT_TRIANGLE_ALTERNATE_GRADIENT_REF      : 1;
        unsigned NEW_QUAD_DECOMPOSITION                     : 1;
        unsigned                                            : 8;
    } gfx9;

    unsigned u32All;

};

// Represent register fields of PA_CL_CLIP_CNTL
union PaClClipCntl
{
    struct
    {
		unsigned UCP_ENA_0                  : 1;
		unsigned UCP_ENA_1                  : 1;
		unsigned UCP_ENA_2                  : 1;
		unsigned UCP_ENA_3                  : 1;
		unsigned UCP_ENA_4                  : 1;
		unsigned UCP_ENA_5                  : 1;
		unsigned                            : 7;
		unsigned PS_UCP_Y_SCALE_NEG         : 1;
		unsigned PS_UCP_MODE                : 2;
		unsigned CLIP_DISABLE               : 1;
		unsigned UCP_CULL_ONLY_ENA          : 1;
		unsigned BOUNDARY_EDGE_FLAG_ENA     : 1;
		unsigned DX_CLIP_SPACE_DEF          : 1;
		unsigned DIS_CLIP_ERR_DETECT        : 1;
		unsigned VTX_KILL_OR                : 1;
		unsigned DX_RASTERIZATION_KILL      : 1;
		unsigned                            : 1;
		unsigned DX_LINEAR_ATTR_CLIP_ENA    : 1;
		unsigned VTE_VPORT_PROVOKE_DISABLE  : 1;
		unsigned ZCLIP_NEAR_DISABLE         : 1;
		unsigned ZCLIP_FAR_DISABLE          : 1;
		unsigned                            : 4;
	} bits;

	unsigned u32All;
};

// Represent register fields PA_CL_VTE_CNTL
union PaClVteCntl
{
    struct
    {
		unsigned VPORT_X_SCALE_ENA      : 1;
		unsigned VPORT_X_OFFSET_ENA     : 1;
		unsigned VPORT_Y_SCALE_ENA      : 1;
		unsigned VPORT_Y_OFFSET_ENA     : 1;
		unsigned VPORT_Z_SCALE_ENA      : 1;
		unsigned VPORT_Z_OFFSET_ENA     : 1;
		unsigned                        : 2;
		unsigned VTX_XY_FMT             : 1;
		unsigned VTX_Z_FMT              : 1;
		unsigned VTX_W0_FMT             : 1;
		unsigned PERFCOUNTER_REF        : 1;
		unsigned                        : 20;
	} bits;

	unsigned u32All;
};

// Enumerates how to render front-facing polygons
enum PolyModeType
{
    POLY_MODE_POINTS        = 0,
    POLY_MODE_LINES         = 1,
    POLY_MODE_TRIANGLES     = 2,
};

// Represents the coherent flag used in buffer intrinsics
union CoherentFlag
{
    struct
    {
        unsigned glc    :  1;   // Global level coherence
        unsigned slc    :  1;   // System level coherence
        unsigned dlc    :  1;   // Device level coherence
        unsigned swz    :  1;   // Swizzled buffer
        unsigned        :  28;
    } bits;

    unsigned u32All;
};

// Represents the combine format used in tbuffer intrinsics
union CombineFormat
{
    struct
    {
        unsigned dfmt   :  4;   // Data format
        unsigned nfmt   :  3;   // Numeric format
        unsigned        :  25;
    } bits;

    unsigned u32All;
};

// Count of user SGPRs used in copy shader
static const unsigned CopyShaderUserSgprCount = 4;

// User SGPR index for the stream info in copy shader
static const unsigned CopyShaderUserSgprIdxStreamInfo = 4;

// User SGPR index for the stream-out write index in copy shader
static const unsigned CopyShaderUserSgprIdxWriteIndex = 5;

// User SGPR index for the stream offsets in copy shader
static const unsigned CopyShaderUserSgprIdxStreamOffset = 6;

// Start offset of currently-processed vertex in GS-VS ring buffer
static const unsigned CopyShaderUserSgprIdxVertexOffset = 10;

} // lgc
