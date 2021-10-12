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

#define IMGUI_WINDOW void
typedef u32 ImGuiID;
typedef u32 ImU32;

/// <summary>
/// imAnim is a functor that takes a Window, some properties about a control (hovered, held, etc.) 
/// </summary>
struct JGSW_API imAnim
{
    virtual ~imAnim() = default;

protected:
    bool m_prevPressed = false;
    bool m_prevHeld = false;
    bool m_prevHovered = false;
};

/// <summary>
/// The template version of imAnim is imAnimCtrl, and it specifies the actual return type of the functor.
/// </summary>
/// <typeparam name="T"></typeparam>
template <typename T>
struct JGSW_API imAnimCtrl : public imAnim
{
    virtual T operator()(IMGUI_WINDOW* window, bool hovered, bool held, bool pressed) = 0;
};

/// <summary>
/// An initialization struct for imColorAnim
/// </summary>
struct imColorAnimArgs
{
    ImU32 inactiveCol;
    ImU32 hoveredCol;
    ImU32 heldCol;
    float hovAnim_s;    // The number of seconds it takes to go from inactiveCol to hoveredCol
};

/// <summary>
/// An imAnimCtrl<u32> that returns a packed 32-bit color interpolated between the hovered color, the inactive color, and the active color
/// based on the hovAnim_s.
/// </summary>
struct JGSW_API imColorAnim : public imAnimCtrl<ImU32>
{
    imColorAnim(imColorAnimArgs args);
    ImU32 operator()(IMGUI_WINDOW* window, bool hovered, bool held, bool pressed) override;

    static imColorAnim IconHighlight();

private:
    float m_t = 0.0f;
    imColorAnimArgs m_args;
    Vector4 m_inactiveReal, m_hoveredReal, m_distReal;
};

#define ANIM_CTRL(t, ctrl) dynamic_cast<imAnimCtrl<t>&>(*ctrl)

template<typename T, typename U>
using imMap = std::map<T, U>;

#endif // _JSE_IM_ANIM_H_
