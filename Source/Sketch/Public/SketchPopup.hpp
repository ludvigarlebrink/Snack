#pragma once

#include "BaseTypes.hpp"

#include <glm/glm.hpp>
#include <string>

namespace spy
{
class SKETCH_API SketchPopup
{
public:

    static bool BeginContext(const std::string& id);

    static bool BeginContext(uint64 id);

    static bool BeginModal(const std::string& label);

    static bool BeginModal(const std::string& label, const glm::vec2& size);

    static void Close();

    static bool Dialog(const std::string& label, const std::string& description, const std::string& applyButtonText, const std::string& cancelButtonLabel, std::string& output);

    static bool DialogYesNo(const std::string& label, const std::string& description);

    static void End();

    /**
     * @brief Open a popup menu from another popup menu with a menu item.
     */
    static bool MenuItemOpenPopup(const std::string& label, const std::string& popupLabel);

    static void OpenPopup(const std::string& label);
};
} // namespace spy
