/*********************************************************************
 * jseImAnim.h
 *
 * Author: Luke Randazzo <jl_randazzo@hotmail.com>
 * Originally created: September 2021
 *********************************************************************/
#ifndef _JSE_IM_ANIM_H_
#define _JSE_IM_ANIM_H_

#include <map>
#include <Math/LinAlg.h>

class ImGuiWindow;
typedef u32 ImGuiID;
typedef u32 ImU32;

/// <summary>
/// jseImAnim is a functor that takes a Window, some properties about a control (hovered, held, etc.) 
/// </summary>
struct jseImAnim
{
    virtual ~jseImAnim() = default;

protected:
    bool m_prevPressed = false;
    bool m_prevHeld = false;
    bool m_prevHovered = false;
};

template <typename T>
struct jseImAnimCtrl : public jseImAnim
{
    virtual T operator()(ImGuiWindow* window, bool hovered, bool held, bool pressed) = 0;
};

struct jseColorAnimArgs
{
    ImU32 inactiveCol;
    ImU32 hoveredCol;
    ImU32 heldCol;
    float hovAnim_s;    // The number of seconds it takes to go from inactiveCol to hoveredCol
};

struct jseColorAnim : public jseImAnimCtrl<ImU32>
{
    jseColorAnim(jseColorAnimArgs args);
    ImU32 operator()(ImGuiWindow* window, bool hovered, bool held, bool pressed) override;

private:
    float m_t = 0.0f;
    jseColorAnimArgs m_args;
    Vector4 m_inactiveReal, m_hoveredReal, m_distReal;
};

#define ANIM_CTRL(t, ctrl) dynamic_cast<jseImAnimCtrl<t>&>(*ctrl)

template<typename T, typename U>
using jseImMap = std::map<T, U>;

#endif // _JSE_IM_ANIM_H_
