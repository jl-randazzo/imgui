#include "jseImAnim.h"
#include "imgui_internal.h"
#include "Debug/j_log.h"

//////////////////////////////////////////////////////////////////////////

Vector4 MakeFloats(u32 v)
{
    float r = (v & 0xFF000000) >> 24;
    float g = (v & 0x00FF0000) >> 16;
    float b = (v & 0x0000FF00) >> 8;
    float a = (v & 0x000000FF);

    return Vector4(r, g, b, a);
}

//////////////////////////////////////////////////////////////////////////

u32 MakeU32(Vector4 vec)
{
    u32 r = ((u32)vec.x) << 24;
    u32 g = ((u32)vec.y) << 16;
    u32 b = ((u32)vec.z) << 8;
    u32 a = ((u32)vec.w);
    return r | g | b | a;
}

//////////////////////////////////////////////////////////////////////////

jseColorAnim::jseColorAnim(jseColorAnimArgs args) : m_args(args), m_inactiveReal(MakeFloats(args.inactiveCol)), m_hoveredReal(MakeFloats(args.hoveredCol)), m_distReal(m_hoveredReal - m_inactiveReal)
{
}

//////////////////////////////////////////////////////////////////////////

ImU32 jseColorAnim::operator()(ImGuiWindow*, bool hovered, bool held, bool pressed)
{
    float dt = (float)GImGui->IO.DeltaTime;
    if (hovered)
    {
        m_t += m_t < m_args.hovAnim_s ? dt : 0;
        m_t = m_t > m_args.hovAnim_s ? m_args.hovAnim_s : m_t;
    }
    else if (m_t > 0)
    {
        m_t -= dt;
        m_t = m_t < 0 ? 0 : m_t;
    }

    if (hovered && held)
    {
        return m_args.heldCol;
    }

    float t = m_t / m_args.hovAnim_s;
    Vector4 dist = t * m_distReal;

    Vector4 res = dist + m_inactiveReal;

    return MakeU32(res);
}

//////////////////////////////////////////////////////////////////////////
