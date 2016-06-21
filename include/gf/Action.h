/*
 * Gamedev Framework (gf)
 * Copyright (C) 2016 Julien Bernard
 *
 * This software is provided 'as-is', without any express or implied
 * warranty.  In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software
 *    in a product, an acknowledgment in the product documentation would be
 *    appreciated but is not required.
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 */
#ifndef GF_ACTION_H
#define GF_ACTION_H

#include <memory>
#include <string>
#include <vector>

#include "Control.h"
#include "Gamepad.h"
#include "Keyboard.h"
#include "Mouse.h"
#include "Portability.h"

namespace gf {
#ifndef DOXYGEN_SHOULD_SKIP_THIS
inline namespace v1 {
#endif

  struct Event;

  /**
   * @ingroup window
   * @brief An action that can be triggered by different controls.
   *
   */
  class GF_API Action {
  public:
    /**
     * @brief Construct an action with a name.
     *
     * @param name the name of the action.
     */
    Action(std::string name);

    /**
     * @brief Get the name of the action.
     *
     * @return the name of the action.
     */
    const std::string& getName() const {
      return m_name;
    }

    /**
     * @name Type of the action
     * @{
     */
    /**
     * @brief Set the action continuous.
     *
     * A continuous action is an action that is active as long as the user do
     * not desactivate it. A reset() call does not desactivate the action.
     *
     * @sa reset(), setInstantaneous()
     */
    void setContinuous();

    /**
     * @brief Check if the action is continuous.
     *
     * @return true if the action is continuous.
     */
    bool isContinuous() const;

    /**
     * @brief Set the action instantaneous.
     *
     * An instantaneous action is an action that is active until the next
     * reset() call.
     *
     * @sa reset(), setContinuous()
     */
    void setInstantaneous();

    /**
     * @brief Check if the action is instantaneous.
     *
     * @return true if the action is instantaneous.
     */
    bool isInstantaneous() const;
    /** @} */

    /**
     * @name Controls for the action
     * @{
     */

    /**
     * @brief Add a key control.
     *
     * @param code the keycode of the key
     *
     * @sa KeycodeKeyControl
     */
    void addKeycodeKeyControl(Keycode code);

    /**
     * @brief Add a key control.
     *
     * @param code the scancode of the key
     *
     * @sa ScancodeKeyControl
     */
    void addScancodeKeyControl(Scancode code);

    /**
     * @brief Add a mouse button control.
     *
     * @param button the button of the mouse.
     *
     * @sa MouseButtonControl
     */
    void addMouseButtonControl(MouseButton button);

    /**
     * @brief Add a gamepad button control.
     *
     * @param id the id of the gamepad.
     * @param button the button of the gamepad
     *
     * @sa GamepadButtonControl
     */
    void addGamepadButtonControl(GamepadId id, GamepadButton button);

    /**
     * @brief Add a gamepad axis control.
     *
     * @param id the id of the gamepad.
     * @param axis the axis of the gamepad.
     * @param dir the direction of the axis of the gamepad.
     *
     * @sa GamepadAxisControl
     */
    void addGamepadAxisControl(GamepadId id, GamepadAxis axis, GamepadAxisDirection dir);

    /**
     * @brief Add a close control.
     *
     * @sa CloseControl
     */
    void addCloseControl();
    /** @} */

    /**
     * @name State of the action
     * @{
     */
    /**
     * @brief Update the state of the action thanks to an event.
     *
     * @param event the event to update the action.
     *
     * @sa Control::update()
     */
    void update(const Event& event);

    /**
     * @brief Check if the action is active.
     *
     * An action is active if at least one of its control is active.
     *
     * @return true if the action is active.
     *
     * @sa Control::isActive()
     */
    bool isActive();

    /**
     * @brief Reset the state of the action.
     *
     * This function depends of the type of the action.
     *
     * @sa setContinuous(), setInstantaneous(), Control::reset()
     */
    void reset();
    /** @} */

  private:
    enum class Type {
      INSTANTANEOUS,
      CONTINUOUS,
    };

    std::string m_name;
    Type m_type;
    std::vector<std::unique_ptr<Control>> m_controls;
  };

  /**
   * @ingroup window
   * @brief A set of actions.
   *
   */
  class GF_API ActionContainer {
  public:
    /**
     * @brief Add an action.
     *
     * @param action the action to add to the set.
     */
    void addAction(Action& action);

    /**
     * @brief Update all the actions.
     *
     * @param event the event to update the actions.
     *
     * @sa Action;:update()
     */
    void update(const Event& event);

    /**
     * @brief Reset all the actions.
     *
     * @sa Action::reset()
     */
    void reset();

  private:
    std::vector<Action*> m_actions;
  };

#ifndef DOXYGEN_SHOULD_SKIP_THIS
}
#endif
}

#endif // GF_ACTION_H