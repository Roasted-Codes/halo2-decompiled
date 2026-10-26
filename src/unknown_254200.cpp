// @flags /O2 /arch:SSE /Gr
#include "shader_storage.h"
#include "view_context_storage.h"
#include "unknown_11c920.h"
#include "globals.h"
#include <xtl.h>
#include <string.h>
#include "unknown_13927e.h"

struct s_bitmap_view;
struct s_type_7ba8e9;
D3DTexture *function_12360(s_bitmap_view *arg_0, real arg_1);
bool function_14390(short arg_0, s_type_7ba8e9 *arg_1, real arg_2);
void function_14bc0(short arg_0, short arg_1, bool arg_2);
dword function_1cc30(long arg_0);
void __stdcall function_1c710(void *arg_0);
void function_15180(D3DPIXELSHADERDEF const *arg_0);
extern long g_4858b8;
extern D3DPIXELSHADERDEF g_484f68;
extern dword g_4b8448, g_4b8308, g_4b82e8, g_4b82f4, g_4b82f8;
extern dword g_4b8324, g_4b82ec, g_4b82e0, g_4b8450;
byte g_51ec9a;
#include "texture_stage_storage.h"
#include "texture_stage_dimensions.h"
D3DTexture *function_12310(s_bitmap_view *arg_0, real arg_1);
void function_1cf50(void);
void function_14f60(short arg_0, short arg_1);
void function_0222d0(D3DRENDERSTATETYPE arg_0, dword arg_1);
void function_0224f0(dword arg_0, D3DTEXTURESTAGESTATETYPE arg_1, dword arg_2);
real function_1392a9(long arg_0);
extern long g_4ba04c;

PRIVATE __forceinline byte *function_254201(void)
{
	byte *local_0 = (byte *)g_4e034c;
	byte *local_1;
	if (*(long *)(local_0 + 0x110))
	{
		local_1 = *(byte **)(local_0 + 0x114);
	}
	else
	{
		local_1 = NULL;
	}
	return local_1;
}

PRIVATE __forceinline s_bitmap_view *function_254202(long arg_0)
{
	byte *local_0 = g_4e3b44[arg_0 & 0xffff].bytes;
	s_bitmap_view *local_1 = NULL;
	if (local_0 && *(long *)(local_0 + 0x44) > 0)
	{
		local_1 = *(s_bitmap_view **)(local_0 + 0x48);
	}
	return local_1;
}

PRIVATE __forceinline void function_254491(real arg_0, color3f const *arg_1)
{
	real local_0 = arg_1->blue * arg_0;
	real local_1 = arg_1->green * arg_0;
	real local_2 = arg_1->red * arg_0;
	D3DDevice_SetVertexData4f(5, local_2, local_1, local_0, 1.f);
}

#include "frame_storage.h"
#include "reset_storage.h"
extern byte g_4670bc;
struct s_render_reset_state;
void function_16b10(s_render_reset_state *state);
void function_14ac0(void);
void __stdcall function_15720(real x, real y);

#include <stddef.h>
typedef char assert_254200_offset[(offsetof(D3DPIXELSHADERDEF, PSAlphaInputs) == 0) ? 1 : -1];
#define program_words_254200 (&g_484f68.PSAlphaInputs)

__declspec(noinline) void function_254200(void);

// @retail 0x254200
void function_254200(void)
{
    s_bitmap_view *first = function_254202(*(long *)(function_254201() + 0x64));
    s_bitmap_view *second = function_254202(*(long *)(function_254201() + 0x6c));
    g_4670bc = true;
    function_16b10((s_render_reset_state *)g_485b48);
    g_51ec9a = false;
    if (function_12360(first, 0.0f) && function_12360(second, 0.0f))
    {
        g_51ec9a = true;
        function_14bc0(0x1d, 0, false);
        if (g_485607 && !g_4858b8)
            function_14ac0();
        D3DDevice::Clear(0, 0, 0xf0, 0, 1.0f, 0);
        function_15720(0.0f, 0.0f);
        function_14390(0, (s_type_7ba8e9 *)first, 0.0f);
        D3DDevice::SetTextureStageState(0, (D3DTEXTURESTAGESTATETYPE const &)D3DTSS_ADDRESSU, 4);
        D3DDevice::SetTextureStageState(0, (D3DTEXTURESTAGESTATETYPE const &)D3DTSS_ADDRESSV, 4);
        D3DDevice::SetTextureStageState(0, (D3DTEXTURESTAGESTATETYPE const &)D3DTSS_MAGFILTER, 2);
        D3DDevice::SetTextureStageState(0, (D3DTEXTURESTAGESTATETYPE const &)D3DTSS_MINFILTER, 2);
        D3DDevice::SetTextureStageState(0, (D3DTEXTURESTAGESTATETYPE const &)D3DTSS_MIPFILTER, 1);
        D3DDevice::SetTextureStageState(0, (D3DTEXTURESTAGESTATETYPE const &)D3DTSS_MAXANISOTROPY, 0);
        D3DDevice::SetTextureStageState(0, (D3DTEXTURESTAGESTATETYPE const &)D3DTSS_MIPMAPLODBIAS, 0);
        D3DDevice::SetTextureStageState(0, (D3DTEXTURESTAGESTATETYPE const &)D3DTSS_MAXMIPLEVEL, 0);
        D3DDevice::SetTextureStageState(0, (D3DTEXTURESTAGESTATETYPE const &)D3DTSS_COLORSIGN, 0);
        D3DDevice::SetTextureStageState(0, (D3DTEXTURESTAGESTATETYPE const &)D3DTSS_ALPHAKILL, 0);
        g_4b8448 = 0x901;
        D3DDevice::SetRenderState(D3DRS_CULLMODE, 0x901);
        g_4b8308 = 0x10101;
        D3DDevice::SetRenderState(D3DRS_COLORWRITEENABLE, 0x10101);
        g_4b82e8 = 1;
        D3DDevice::SetRenderState(D3DRS_ALPHABLENDENABLE, 1);
        g_4b82f4 = 1;
        D3DDevice::SetRenderState(D3DRS_SRCBLEND, 1);
        g_4b82f8 = 1;
        D3DDevice::SetRenderState(D3DRS_DESTBLEND, 1);
        g_4b8324 = 0x8006;
        D3DDevice::SetRenderState(D3DRS_BLENDOP, 0x8006);
        g_4b82ec = 0;
        D3DDevice::SetRenderState(D3DRS_ALPHATESTENABLE, 0);
        g_4b82e0 = 0x207;
        D3DDevice::SetRenderState(D3DRS_ZFUNC, 0x207);
        g_4b8450 = 0;
        D3DDevice::SetRenderState(D3DRS_ZBIAS, 0);
        function_1cc30(12);
        function_1c710(g_51f0f0);
        memset((D3DPIXELSHADERDEF *)program_words_254200, 0, sizeof(g_484f68));
        g_484f68.PSTextureModes = 1;
        g_484f68.PSCombinerCount = 1;
        g_484f68.PSFinalCombinerInputsABCD = 0x8040000;
        function_15180((D3DPIXELSHADERDEF *)program_words_254200);
    }
}

#undef program_words_254200

// score 4 (was 4): two depth/top-edge reload pairs remain.
// shared left edge lifetimes 162;
// shared right edge lifetimes 118;
// shared left/right edge lifetimes 171;
// shared bottom edge lifetimes 150;
// shared left/bottom edge lifetimes 146;
// shared right/bottom edge lifetimes 142;
// shared left/right/bottom edge lifetimes 189;
// read-only point and extent snapshots 4;
// @retail 0x254490
void __stdcall function_254490(point2f const *arg_0, real arg_1, real arg_2, color3f const *arg_3, bool arg_4)
{
	s_bitmap_view *local_0 = function_254202(*(long *)(function_254201() + 0x64));
	s_bitmap_view *local_1 = function_254202(*(long *)(function_254201() + 0x6c));
	if (function_12360(local_0, 0.f) && function_12360(local_1, 0.f))
	{
		s_bitmap_view *local_2 = arg_4 ? local_1 : local_0;
		if (local_2)
		{
			g_51f3c8[1][0] = function_12310(local_2, 0.f);
			long local_8 = *(short *)((byte *)local_2 + 6);
			long local_9 = *(short *)((byte *)local_2 + 4);
			g_485af4[0] = local_9;
			g_485b04[0] = local_8;
		}
		if (g_51ec9a)
		{
			real local_4 = arg_2 * 2.f;
			point2f local_3 = *arg_0;
			function_1cf50();
			function_1c710(g_51f0f0);
			g_4b8448 = 0;
			D3DDevice_SetRenderState(D3DRS_CULLMODE, 0);
			g_4b8450 = 0;
			D3DDevice_SetRenderState(D3DRS_ZBIAS, 0);
			D3DDevice::Begin(D3DPT_TRIANGLEFAN);
			function_254491(arg_1, arg_3);
			D3DDevice::SetVertexData2s(1, 0, 0);
			D3DDevice_SetVertexData4f(D3DVSDE_VERTEX, local_3.x - local_4, local_3.y + local_4, 16777215.f, 16777215.f);
			D3DDevice::SetVertexData2s(1, 1, 0);
			D3DDevice_SetVertexData4f(D3DVSDE_VERTEX, local_3.x + local_4, local_3.y + local_4, 16777215.f, 16777215.f);
			D3DDevice::SetVertexData2s(1, 1, 1);
			D3DDevice_SetVertexData4f(D3DVSDE_VERTEX, local_3.x + local_4, local_3.y - local_4, 16777215.f, 16777215.f);
			D3DDevice::SetVertexData2s(1, 0, 1);
			D3DDevice_SetVertexData4f(D3DVSDE_VERTEX, local_3.x - local_4, local_3.y - local_4, 16777215.f, 16777215.f);
			D3DDevice_End();
		}
	}
}

// score 153 (was 153): frame 0x14 versus 0x10; coordinate spills and reservation scheduling differ.
// Frame 0x14 versus 0x10 and reservation/coordinate homes remain. Fast control
// 246; final/entry center values 307/590; edge values 322; center with edges 301; signed alpha/C++
// color/both 246 each; alpha with edges 322; native color reference 276; color copies after
// Begin/commit 293/311.
// frame 0x14 versus 0x10; coordinate spills and reservation scheduling differ.
// Frame 0x14 versus 0x10; coordinate spills and first reservation scheduling remain.
// Earlier 237 (was 276): frame 0x14 versus 0x10; coordinate spills and reservation scheduling differ.
// frame 0x14 versus 0x10; color/coordinate spills and reservation scheduling remain.
// Native color value 246 fast / 237 plain; value half-size 276; replicated alpha 349;
// alpha after clear 265; second coordinate C entry 403; color with later alpha 252;
// memcpy color 246. Only the native color value is kept.
// Previously 276 (was 342): frame 0x10 agreed; texture-factor homes and reservation scheduling differed.
// Value half-size 342; disabled-path return 342; C begin/vertex calls 561;
// C texture-state calls 455; role-named texture coordinates 342.
// First-quad scope 342; texture expressions at calls 386; C++ color entry 342;
// complete descriptor value initialization 619; parallel alpha-byte packing 342.
// Coordinates before inlined begin 376; scale-parameter half-span 342; function-scope coordinates 342;
// shared resource pointer 511; dword alpha carrier 276.
// First coordinate C entry 373; folded half-span with inline reservations 276;
// delayed lower coordinate 387; delayed upper coordinate 384; lower initialized first 359.
// Shared color output 246; pointer/helper 276 (exact-only); consumer query/helper 305; byte alpha 166 fast / 157 plain; SDK packing 170; texture-mode-first stores 246 (fast control 246).
// Round 109: Fast: native color/coordinate names 246; color phase scope 246; final half-size value with native color 246; color after texture commit 248; immutable native color 246 (opening fast 246, plain 237).
// Result pointer 276; color query after Begin 263; function color lifetime/immutable alpha/
// chained descriptor counts/final short-coordinate API/half-scale product order/
// upper-coordinate term order 246/246/246/246/246/246 (opening fast 246, plain 237).
// Opening executable body and all inherited directives restored.
// Current native-color/byte-alpha frame: scoped color 166 fast; scalar half-size 166; disabled return 166; full
// readiness guards 166; lower coordinate first 378 (control 166). Pointer/byte controls 342 and value-half/pointer
// 342 reproduce older configurations and are excluded.
// Current byte-alpha frame: color after Begin 192; color after commit 168; C++ color entry 166; first position C++
// entry 166; second quad real-table loop 412 (fast control 166). Frame/color/reservation homes remain; complete
// opening body restored.
// Native memcpy in byte-alpha frame 166; complete component initializer 171; shared color helper with byte alpha 166;
// word alpha 162 fast / 153 plain (kept); explicit half-size assignments with word alpha 162 fast.
// Round 210: Signed-word alpha 162; coordinate lexical homes 162; immutable value half-size 162;
// native channel packing 238; chained descriptor counts 162 (fast control 162). Frame and
// reservation scheduling remain.
// Round 212: Immutable bitmap pointers/repeated texture coordinates 162/162; chained RGB/alpha outputs 165; shared color output with word alpha 162; center snapshot at first final vertex 296 (fast control 162). Frame and reservation scheduling remain.
// Round 157: Word-alpha frame: second/both expanded position device entries 162/162; first/second
// coordinate C entry 443/443; complete first-quad device entries 162; native color input reference
// alone/second position/color entry 349/349/349 (fast control 162, plain 153).
// @retail 0x2548f0
void __stdcall function_2548f0(point2f const *arg_0, real arg_1)
{
	s_bitmap_view *local_0 = function_254202(*(long *)(function_254201() + 0x3c));
	s_bitmap_view *local_1 = function_254202(*(long *)(function_254201() + 0x44));
	if (g_51ec9a)
	{
		if (function_12360(local_0, 0.f) && function_12360(local_1, 0.f))
		{
			g_4b8448 = 0x901;
			D3DDevice_SetRenderState(D3DRS_CULLMODE, 0x901);
			g_4b8308 = 0x10101;
			D3DDevice_SetRenderState(D3DRS_COLORWRITEENABLE, 0x10101);
			g_4b82e8 = 1;
			D3DDevice_SetRenderState(D3DRS_ALPHABLENDENABLE, 1);
			g_4b8324 = 0x8006;
			D3DDevice_SetRenderState(D3DRS_BLENDOP, 0x8006);
			g_4b82ec = 0;
			D3DDevice_SetRenderState(D3DRS_ALPHATESTENABLE, 0);
			g_4b82e0 = 0x207;
			D3DDevice_SetRenderState(D3DRS_ZFUNC, 0x207);
			g_4b8450 = 0;
			D3DDevice_SetRenderState(D3DRS_ZBIAS, 0);
			function_14390(0, (s_type_7ba8e9 *)local_0, 0.f);
			D3DDevice::SetTextureStageState(0, (D3DTEXTURESTAGESTATETYPE const &)D3DTSS_ADDRESSU, 4);
			D3DDevice::SetTextureStageState(0, (D3DTEXTURESTAGESTATETYPE const &)D3DTSS_ADDRESSV, 4);
			D3DDevice::SetTextureStageState(0, (D3DTEXTURESTAGESTATETYPE const &)D3DTSS_BORDERCOLOR, 0x46000000);
			D3DDevice::SetTextureStageState(0, (D3DTEXTURESTAGESTATETYPE const &)D3DTSS_MAGFILTER, 2);
			D3DDevice::SetTextureStageState(0, (D3DTEXTURESTAGESTATETYPE const &)D3DTSS_MINFILTER, 2);
			D3DDevice::SetTextureStageState(0, (D3DTEXTURESTAGESTATETYPE const &)D3DTSS_MIPFILTER, 1);
			D3DDevice::SetTextureStageState(0, (D3DTEXTURESTAGESTATETYPE const &)D3DTSS_MAXANISOTROPY, 0);
			D3DDevice::SetTextureStageState(0, (D3DTEXTURESTAGESTATETYPE const &)D3DTSS_MIPMAPLODBIAS, 0);
			D3DDevice::SetTextureStageState(0, (D3DTEXTURESTAGESTATETYPE const &)D3DTSS_MAXMIPLEVEL, 0);
			D3DDevice::SetTextureStageState(0, (D3DTEXTURESTAGESTATETYPE const &)D3DTSS_COLORSIGN, 0);
			D3DDevice::SetTextureStageState(0, (D3DTEXTURESTAGESTATETYPE const &)D3DTSS_ALPHAKILL, 0);
			g_4b82f4 = 1;
			D3DDevice_SetRenderState(D3DRS_SRCBLEND, 1);
			g_4b82f8 = 0x302;
			D3DDevice_SetRenderState(D3DRS_DESTBLEND, 0x302);
			function_1cc30(0xc);
			function_1c710(g_51f0f0);
			memset(&g_484f68, 0, sizeof(g_484f68));
			g_484f68.PSCombinerCount = 1;
			g_484f68.PSTextureModes = 1;
			g_484f68.PSRGBInputs[0] = 0x8040000;
			g_484f68.PSRGBOutputs[0] = 0xc0;
			g_484f68.PSAlphaInputs[0] = 0x18140000;
			g_484f68.PSAlphaOutputs[0] = 0xc0;
			g_484f68.PSFinalCombinerInputsABCD = 0xc;
			g_484f68.PSFinalCombinerInputsEFG = 0x1c00;
			function_15180(&g_484f68);
			color3f color = *(color3f const *)function_13927e(g_4b9ed8);
			function_1cf50();
			D3DDevice::Begin(D3DPT_TRIANGLEFAN);
			D3DDevice_SetVertexData4f(5, color.red, color.green, color.blue, 1.f);
			real local_3 = arg_1 * 0.5f;
			real local_4 = local_3 + 0.5f;
			real local_5 = 0.5f - local_3;
			D3DDevice::SetVertexData2f(1, local_4, local_5);
			D3DDevice_SetVertexData4f(D3DVSDE_VERTEX, 0.f, 0.f, 16777215.f, 16777215.f);
			D3DDevice::SetVertexData2f(1, local_5, local_5);
			D3DDevice_SetVertexData4f(D3DVSDE_VERTEX, 64.f, 0.f, 16777215.f, 16777215.f);
			#pragma inline_depth(0)
			D3DDevice_SetVertexData2f(1, local_5, local_4);
			D3DDevice_SetVertexData4f(D3DVSDE_VERTEX, 64.f, 64.f, 16777215.f, 16777215.f);
			D3DDevice_SetVertexData2f(1, local_4, local_4);
			D3DDevice_SetVertexData4f(D3DVSDE_VERTEX, 0.f, 64.f, 16777215.f, 16777215.f);
			D3DDevice_End();
			#pragma inline_depth()
			function_14390(0, (s_type_7ba8e9 *)local_1, 0.f);
#pragma inline_depth(0)
			function_0222d0((D3DRENDERSTATETYPE)0x3e, 0);
			function_0222d0((D3DRENDERSTATETYPE)0x3f, 0x302);
#pragma inline_depth()
			memset(&g_484f68, 0, sizeof(g_484f68));
			g_484f68.PSCombinerCount = 1;
			g_484f68.PSTextureModes = 1;
			g_484f68.PSFinalCombinerInputsABCD = 8;
			g_484f68.PSFinalCombinerInputsEFG = 0x1800;
			function_15180(&g_484f68);
			function_1cf50();
			#pragma inline_depth(0)
			D3DDevice_Begin(D3DPT_TRIANGLEFAN);
			D3DDevice_SetVertexData4f(5, 0.4f, 0.8f, 0.4f, 1.f);
			D3DDevice_SetVertexData2f(1, 1.f, 0.f);
			D3DDevice_SetVertexData4f(D3DVSDE_VERTEX, 0.f, 0.f, 16777215.f, 16777215.f);
			D3DDevice_SetVertexData2f(1, 0.f, 0.f);
			D3DDevice_SetVertexData4f(D3DVSDE_VERTEX, 64.f, 0.f, 16777215.f, 16777215.f);
			D3DDevice_SetVertexData2f(1, 0.f, 1.f);
			D3DDevice_SetVertexData4f(D3DVSDE_VERTEX, 64.f, 64.f, 16777215.f, 16777215.f);
			D3DDevice_SetVertexData2f(1, 1.f, 1.f);
			D3DDevice_SetVertexData4f(D3DVSDE_VERTEX, 0.f, 64.f, 16777215.f, 16777215.f);
			D3DDevice_End();
			function_14bc0((short)g_4858b8, 0, true);
			function_14f60(0, 0x1d);
			function_0224f0(0, (D3DTEXTURESTAGESTATETYPE)0, 3);
			function_0224f0(0, (D3DTEXTURESTAGESTATETYPE)1, 3);
			function_0224f0(0, (D3DTEXTURESTAGESTATETYPE)3, 2);
			function_0224f0(0, (D3DTEXTURESTAGESTATETYPE)4, 2);
			function_0224f0(0, (D3DTEXTURESTAGESTATETYPE)5, 1);
			#pragma inline_depth()
			D3DDevice_SetTextureStageState(0, D3DTSS_BORDERCOLOR, 0);
			#pragma inline_depth(0)
			function_0224f0(0, D3DTSS_MAXANISOTROPY, 0);
			function_0224f0(0, D3DTSS_MIPMAPLODBIAS, 0);
			function_0224f0(0, D3DTSS_MAXMIPLEVEL, 0);
			function_0224f0(0, D3DTSS_COLORSIGN, 0);
			function_0224f0(0, D3DTSS_ALPHAKILL, 0);
			function_0222d0((D3DRENDERSTATETYPE)0x3e, 1);
			function_0222d0((D3DRENDERSTATETYPE)0x3f, 0x303);
			word local_6 = (byte)(long)(function_1392a9(g_4b9ed8) * 255.f);
			memset(&g_484f68, 0, sizeof(g_484f68));
			g_484f68.PSConstant0[0] = (((((dword)local_6 << 8) | local_6) << 8 | local_6) << 8) | local_6;
			g_484f68.PSCombinerCount = 1;
			g_484f68.PSTextureModes = 1;
			g_484f68.PSRGBInputs[0] = 0x8010000;
			g_484f68.PSRGBOutputs[0] = 0x80;
			g_484f68.PSAlphaInputs[0] = 0x18110000;
			g_484f68.PSAlphaOutputs[0] = 0x80;
			g_484f68.PSFinalCombinerConstant0 = 0xff00ff00;
			g_484f68.PSFinalCombinerInputsABCD = 8;
			g_484f68.PSFinalCombinerInputsEFG = 0x1800;
			function_15180(&g_484f68);
			real const &local_7 = g_4ba04c > 1 ? 32.f : 42.f;
			function_1cf50();
			D3DDevice_Begin(D3DPT_TRIANGLEFAN);
			D3DDevice_SetVertexData2s(1, 0, 0);
			D3DDevice_SetVertexData4f(D3DVSDE_VERTEX, arg_0->x - local_7, arg_0->y - local_7, 16777215.f, 16777215.f);
			D3DDevice_SetVertexData2s(1, 1, 0);
			D3DDevice_SetVertexData4f(D3DVSDE_VERTEX, arg_0->x + local_7, arg_0->y - local_7, 16777215.f, 16777215.f);
			D3DDevice_SetVertexData2s(1, 1, 1);
			D3DDevice_SetVertexData4f(D3DVSDE_VERTEX, arg_0->x + local_7, arg_0->y + local_7, 16777215.f, 16777215.f);
			D3DDevice_SetVertexData2s(1, 0, 1);
			D3DDevice_SetVertexData4f(D3DVSDE_VERTEX, arg_0->x - local_7, arg_0->y + local_7, 16777215.f, 16777215.f);
			D3DDevice_End();
			#pragma inline_depth(255)
		}
		else if (g_51ec9a)
		{
			function_14bc0((short)g_4858b8, 0, true);
		}
	}
}
