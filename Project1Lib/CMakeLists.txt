project(Project1Lib)

set(SOURCE_FILES Level.cpp Level.h
                MainFrame.cpp MainFrame.h
                Game.cpp Game.h
                GameView.cpp GameView.cpp
            Item.cpp Item.h
            pch.h
            XRay.cpp  XRay.h
            Cauldron.cpp Cauldron.h
            Sparty.h Sparty.cpp
        Background.cpp
        Background.h
        XMLItem.cpp
        XMLItem.h
        Pumpkin.cpp
        Pumpkin.h
        Digits.cpp
        Digits.h
        ItemVisitor.cpp
        ItemVisitor.h
        Container.cpp
        Container.h
        RedDigit.cpp
        RedDigit.h
        ContainerVisitor.cpp
        ContainerVisitor.h
        DigitVisitor.cpp
        DigitVisitor.h
        ErrorMessage.cpp
        ErrorMessage.h
)

set(wxBUILD_PRECOMP OFF)
find_package(wxWidgets COMPONENTS core base xrc html xml REQUIRED)

include(${wxWidgets_USE_FILE})

add_library(${PROJECT_NAME} STATIC ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} ${wxWidgets_LIBRARIES})

target_precompile_headers(${PROJECT_NAME} PRIVATE pch.h)