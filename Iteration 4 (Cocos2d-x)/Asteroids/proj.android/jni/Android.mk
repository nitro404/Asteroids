LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := cocos2dcpp_shared

LOCAL_MODULE_FILENAME := libcocos2dcpp

LOCAL_SRC_FILES := hellocpp/main.cpp \
                   ../../Classes/AppDelegate.cpp \
				   ../../Classes/Utilities/Utilities.cpp \
				   ../../Classes/Utilities/Colour.cpp \
				   ../../Classes/IO/FileReaderMode.cpp \
				   ../../Classes/IO/FileReader.cpp \
				   ../../Classes/Math/ExtendedMath.cpp \
				   ../../Classes/SpriteAnimationSystem/SpriteAnimationType.cpp \
				   ../../Classes/SpriteAnimationSystem/SpriteAnimation.cpp \
				   ../../Classes/SpriteAnimationSystem/SpriteAnimationCollection.cpp \
				   ../../Classes/Entity/Entity.cpp \
				   ../../Classes/Entity/Entity2D.cpp \
				   ../../Classes/Entity/AnimatedEntity2D.cpp \
				   ../../Classes/GameObjects/RotationDirection.cpp \
				   ../../Classes/GameObjects/Projectile.cpp \
				   ../../Classes/GameObjects/SpaceShipMovementDirection.cpp \
				   ../../Classes/GameObjects/SpaceShipColour.cpp \
				   ../../Classes/GameObjects/SpaceShip.cpp \
				   ../../Classes/GameSystems/ProjectileSystem.cpp \
				   ../../Classes/GameSystems/SpaceShipSystem.cpp \
                   ../../Classes/Asteroids.cpp

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes

LOCAL_WHOLE_STATIC_LIBRARIES := cocos2dx_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocosdenshion_static

# LOCAL_WHOLE_STATIC_LIBRARIES += box2d_static
# LOCAL_WHOLE_STATIC_LIBRARIES += cocosbuilder_static
# LOCAL_WHOLE_STATIC_LIBRARIES += spine_static
# LOCAL_WHOLE_STATIC_LIBRARIES += cocostudio_static
# LOCAL_WHOLE_STATIC_LIBRARIES += cocos_network_static
# LOCAL_WHOLE_STATIC_LIBRARIES += cocos_extension_static


include $(BUILD_SHARED_LIBRARY)

$(call import-module,.)
$(call import-module,audio/android)

# $(call import-module,Box2D)
# $(call import-module,editor-support/cocosbuilder)
# $(call import-module,editor-support/spine)
# $(call import-module,editor-support/cocostudio)
# $(call import-module,network)
# $(call import-module,extensions)
