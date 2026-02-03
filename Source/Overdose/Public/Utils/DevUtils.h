#include "Kismet/KismetSystemLibrary.h"

#pragma region LOG
#define USE_LOGS 1
#define LOG(msg) if (USE_LOGS) UKismetSystemLibrary::PrintString(this, msg, true, true)
#define LOG_C(msg, color) if (USE_LOGS) UKismetSystemLibrary::PrintString(this, msg, true, true, FLinearColor(color))
#define LOG_T(msg, time) if (USE_LOGS) UKismetSystemLibrary::PrintString(this, msg, true, true, FLinearColor(0f, 0.66f, 1.0f), time)
#define LOG_CT(msg, color, time) if (USE_LOGS) UKismetSystemLibrary::PrintString(this, msg, true, true, FLinearColor(color), time)
#pragma endregion

#pragma region COMPONENTS_UTILS
#define CREATE(type, name) CreateDefaultSubobject<type>(name)
#define ROOT CreateDefaultSubobject<USceneComponent>("Root")
#pragma endregion

#pragma region TO_STRING
#define FTOS(float_val) FString::SanitizeFloat(float_val)
#define ITOS(int_val) FString::FromInt(int_val)
#pragma endregion

#pragma region TIME
#define DELTATIME GetWorld()->DeltaTimeSeconds
#pragma endregion

#pragma region DEBUG
#define USE_DEBUG 1
#define DEBUG_CIRCLE if (USE_DEBUG) { DrawDebugCircle(GetWorld(), GetActorLocation(), 50, 10, FColor::Red, false, -1, 0, 0, FVector(0, 1, 0), FVector(1, 0, 0), false); }
/// <param name="at">Circle location</param>
#define DEBUG_CIRCLE_A(at) if (USE_DEBUG) { DrawDebugCircle(GetWorld(), at, 50, 10, FColor::Red, false, -1, 0, 0, FVector(0, 1, 0), FVector(1, 0, 0), false); }
/// <param name="radius">Circle radius</param>
#define DEBUG_CIRCLE_R(radius) if (USE_DEBUG) { DrawDebugCircle(GetWorld(), GetActorLocation(), radius, 10, FColor::Red, false, -1, 0, 0, FVector(0, 1, 0), FVector(1, 0, 0), false); }
/// <param name="color">Circle color</param>
#define DEBUG_CIRCLE_C(color) if (USE_DEBUG) { DrawDebugCircle(GetWorld(), GetActorLocation(), 50, 10, color, false, -1, 0, 0, FVector(0, 1, 0), FVector(1, 0, 0), false); }
/// <param name="tickness">Circle lines thickness</param>
#define DEBUG_CIRCLE_T(thickness) if (USE_DEBUG) { DrawDebugCircle(GetWorld(), GetActorLocation(), 50, 10, FColor::Red, false, -1, 0, thickness, FVector(0, 1, 0), FVector(1, 0, 0), false); }
/// <param name="at">Circle location</param>
/// <param name="radius">Circle radius</param>
#define DEBUG_CIRCLE_AR(at, radius) if (USE_DEBUG) { DrawDebugCircle(GetWorld(), at, radius, 10, FColor::Red, false, -1, 0, 0, FVector(0, 1, 0), FVector(1, 0, 0), false); }
/// <param name="at">Circle location</param>
/// <param name="color">Circle color</param>
#define DEBUG_CIRCLE_AC(at, color) if (USE_DEBUG) { DrawDebugCircle(GetWorld(), at, GetActorLocation(), 10, color, false, -1, 0, 0, FVector(0, 1, 0), FVector(1, 0, 0), false); }
/// <param name="at">Circle location</param>
/// <param name="tickness">Circle lines thickness</param>
#define DEBUG_CIRCLE_AT(at, thickness) if (USE_DEBUG) { DrawDebugCircle(GetWorld(), at, GetActorLocation(), 10, color, false, -1, 0, thickness, FVector(0, 1, 0), FVector(1, 0, 0), false); }
/// <param name="radius">Circle radius</param>
/// <param name="color">Circle color</param>
#define DEBUG_CIRCLE_RC(radius, color) if (USE_DEBUG) { DrawDebugCircle(GetWorld(), GetActorLocation(), radius, 10, color, false, -1, 0, 0, FVector(0, 1, 0), FVector(1, 0, 0), false); }
/// <param name="color">Circle color</param>
/// <param name="tickness">Circle lines thickness</param>
#define DEBUG_CIRCLE_CT(color, thickness) if (USE_DEBUG) { DrawDebugCircle(GetWorld(), GetActorLocation(), 50, 10, color, false, -1, 0, thickness, FVector(0, 1, 0), FVector(1, 0, 0), false); }
/// <param name="radius">Circle radius</param>
/// <param name="tickness">Circle lines thickness</param>
#define DEBUG_CIRCLE_RT(radius, thickness) if (USE_DEBUG) { DrawDebugCircle(GetWorld(), GetActorLocation(), radius, 10, FColor::Red, false, -1, 0, thickness, FVector(0, 1, 0), FVector(1, 0, 0), false); }
/// <param name="radius">Circle radius</param>
/// <param name="color">Circle color</param>
/// <param name="tickness">Circle lines thickness</param>
#define DEBUG_CIRCLE_RCT(radius, color, thickness) if (USE_DEBUG) { DrawDebugCircle(GetWorld(), GetActorLocation(), radius, 10, color, false, -1, 0, thickness, FVector(0, 1, 0), FVector(1, 0, 0), false); }
/// <param name="at">Circle location</param>
/// <param name="radius">Circle radius</param>
/// <param name="color">Circle color</param>
#define DEBUG_CIRCLE_ARC(at, radius, color) if (USE_DEBUG) { DrawDebugCircle(GetWorld(), at, radius, 10, color, false, -1, 0, 0, FVector(0, 1, 0), FVector(1, 0, 0), false); }
/// <param name="at">Circle location</param>
/// <param name="radius">Circle radius</param>
/// <param name="tickness">Circle lines thickness</param>
#define DEBUG_CIRCLE_ART(at, radius, thickness) if (USE_DEBUG) { DrawDebugCircle(GetWorld(), at, radius, 10, FColor::Red, false, -1, 0, thickness, FVector(0, 1, 0), FVector(1, 0, 0), false); }
/// <param name="at">Circle location</param>
/// <param name="radius">Circle radius</param>
/// <param name="color">Circle color</param>
/// <param name="tickness">Circle lines thickness</param>
#define DEBUG_CIRCLE_ARCT(at, radius, color, thickness) if (USE_DEBUG) { DrawDebugCircle(GetWorld(), at, radius, 10, color, false, -1, 0, thickness, FVector(0, 1, 0), FVector(1, 0, 0), false); }
#define DEBUG_SPHERE if (USE_DEBUG) { DrawDebugSphere(GetWorld(), GetActorLocation(), 50, 10, FColor::Red, false, -1, 0, 0); }
/// <param name="at">Sphere location</param>
#define DEBUG_SPHERE_A(at) if (USE_DEBUG) { DrawDebugSphere(GetWorld(), at, 50, 10, FColor::Red, false, -1, 0, 0); }
/// <param name="radius">Sphere radius</param>
#define DEBUG_SPHERE_R(radius) if (USE_DEBUG) { DrawDebugSphere(GetWorld(), GetActorLocation(), radius, 10, FColor::Red, false, -1, 0, 0); }
/// <param name="color">Sphere color</param>
#define DEBUG_SPHERE_C(color) if (USE_DEBUG) { DrawDebugSphere(GetWorld(), GetActorLocation(), 50, 10, color, false, -1, 0, 0); }
/// <param name="tickness">Sphere lines thickness</param>
#define DEBUG_SPHERE_T(thickness) if (USE_DEBUG) { DrawDebugSphere(GetWorld(), GetActorLocation(), 50, 10, FColor::Red, false, -1, 0, thickness); }
/// <param name="at">Sphere location</param>
/// <param name="radius">Sphere radius</param>
#define DEBUG_SPHERE_AR(at, radius) if (USE_DEBUG) { DrawDebugSphere(GetWorld(), at, radius, 10, FColor::Red, false, -1, 0, 0); }
/// <param name="at">Sphere location</param>
/// <param name="color">Sphere color</param>
#define DEBUG_SPHERE_AC(at, color) if (USE_DEBUG) { DrawDebugSphere(GetWorld(), at, 50, 10, color, false, -1, 0, 0); }
/// <param name="at">Sphere location</param>
/// <param name="tickness">Sphere lines thickness</param>
#define DEBUG_SPHERE_AT(at, thickness) if (USE_DEBUG) { DrawDebugSphere(GetWorld(), at, 50, 10, FColor::Red, false, -1, 0, thickness); }
/// <param name="radius">Sphere radius</param>
/// <param name="color">Sphere color</param>
#define DEBUG_SPHERE_RC(radius, color) if (USE_DEBUG) { DrawDebugSphere(GetWorld(), GetActorLocation(), radius, 10, color false, -1, 0, 0); }
/// <param name="radius">Sphere radius</param>
/// <param name="tickness">Sphere lines thickness</param>
#define DEBUG_SPHERE_RT(radius, thickness) if (USE_DEBUG) { DrawDebugSphere(GetWorld(), GetActorLocation(), radius, 10, FColor::Red, false, -1, 0, thickness); }
/// <param name="color">Sphere color</param>
/// <param name="tickness">Sphere lines thickness</param>
#define DEBUG_SPHERE_CT(color, thickness) if (USE_DEBUG) { DrawDebugSphere(GetWorld(), GetActorLocation(), 50, 10, color, false, -1, 0, thickness); }
/// <param name="at">Sphere location</param>
/// <param name="radius">Sphere radius</param>
/// <param name="color">Sphere color</param>
#define DEBUG_SPHERE_ARC(at, radius, color) if (USE_DEBUG) { DrawDebugSphere(GetWorld(), at, radius, 10, color, false, -1, 0, 0); }
/// <param name="at">Sphere location</param>
/// <param name="radius">Sphere radius</param>
/// <param name="tickness">Sphere lines thickness</param>
#define DEBUG_SPHERE_ART(at, radius, thickness) if (USE_DEBUG) { DrawDebugSphere(GetWorld(), at, radius, 10, FColor::Red, false, -1, 0, thickness); }
/// <param name="radius">Sphere radius</param>
/// <param name="color">Sphere color</param>
/// <param name="tickness">Sphere lines thickness</param>
#define DEBUG_SPHERE_RCT(radius, color, thickness) if (USE_DEBUG) { DrawDebugSphere(GetWorld(), GetActorLocation(), radius, 10, color, false, -1, 0, thickness); }
/// <param name="at">Sphere location</param>
/// <param name="radius">Sphere radius</param>
/// <param name="color">Sphere color</param>
/// <param name="tickness">Sphere lines thickness</param>
#define DEBUG_SPHERE_ARCT(at, radius, color, thickness) if (USE_DEBUG) { DrawDebugSphere(GetWorld(), at, radius, 10, color, false, -1, 0, thickness); }
#define DEBUG_BOX if (USE_DEBUG) { DrawDebugBox(GetWorld(), GetActorLocation(), FVector(30), FColor::Red, false, -1, 0, 0); }
/// <param name="at">Box location</param>
#define DEBUG_BOX_A(at) if (USE_DEBUG) { DrawDebugBox(GetWorld(), at, FVector(30), FColor::Red, false, -1, 0, 0); }
/// <param name="size">Box size</param>
#define DEBUG_BOX_S(size) if (USE_DEBUG) { DrawDebugBox(GetWorld(), GetActorLocation(), FVector(size), FColor::Red, false, -1, 0, 0); }
/// <param name="color">Box color</param>
#define DEBUG_BOX_C(color) if (USE_DEBUG) { DrawDebugBox(GetWorld(), GetActorLocation(), FVector(30), color, false, -1, 0, 0); }
/// <param name="thickness">Box lines thickness</param>
#define DEBUG_BOX_T(thickness) if (USE_DEBUG) { DrawDebugBox(GetWorld(), GetActorLocation(), FVector(30), FColor::Red, false, -1, 0, thickness); }
/// <param name="at">Box location</param>
/// <param name="size">Box size</param>
#define DEBUG_BOX_AS(at, size) if (USE_DEBUG) { DrawDebugBox(GetWorld(), at, FVector(size), FColor::Red, false, -1, 0, 0); }
/// <param name="at">Box location</param>
/// <param name="color">Box color</param>
#define DEBUG_BOX_AC(at, color) if (USE_DEBUG) { DrawDebugBox(GetWorld(), at, FVector(30), color, false, -1, 0, 0); }
/// <param name="at">Box location</param>
/// <param name="thickness">Box lines thickness</param>
#define DEBUG_BOX_AT(at, thickness) if (USE_DEBUG) { DrawDebugBox(GetWorld(), at, FVector(30), FColor::Red, false, -1, 0, thickness); }
/// <param name="size">Box size</param>
/// <param name="color">Box color</param>
#define DEBUG_BOX_SC(size, color) if (USE_DEBUG) { DrawDebugBox(GetWorld(), GetActorLocation(), FVector(size), color, false, -1, 0, 0); }
/// <param name="size">Box size</param>
/// <param name="thickness">Box lines thickness</param>
#define DEBUG_BOX_ST(size, thickness) if (USE_DEBUG) { DrawDebugBox(GetWorld(), GetActorLocation(), FVector(size), FColor::Red, false, -1, 0, thickness); }
/// <param name="color">Box color</param>
/// <param name="thickness">Box lines thickness</param>
#define DEBUG_BOX_CT(color, thickness) if (USE_DEBUG) { DrawDebugBox(GetWorld(), GetActorLocation(), FVector(30), color, false, -1, 0, thickness); }
/// <param name="at">Box location</param>
/// <param name="size">Box size</param>
/// <param name="color">Box color</param>
#define DEBUG_BOX_ASC(at, size, color) if (USE_DEBUG) { DrawDebugBox(GetWorld(), at, FVector(size), color, false, -1, 0, 0); }
/// <param name="at">Box location</param>
/// <param name="size">Box size</param>
/// <param name="thickness">Box lines thickness</param>
#define DEBUG_BOX_AST(at, size, thickness) if (USE_DEBUG) { DrawDebugBox(GetWorld(), at, FVector(size), FColor::Red, false, -1, 0, thickness); }
/// <param name="size">Box size</param>
/// <param name="color">Box color</param>
/// <param name="thickness">Box lines thickness</param>
#define DEBUG_BOX_SCT(size, color, thickness) if (USE_DEBUG) { DrawDebugBox(GetWorld(), GetActorLocation(), FVector(size), color, false, -1, 0, thickness); }
/// <param name="at">Box location</param>
/// <param name="size">Box size</param>
/// <param name="color">Box color</param>
/// <param name="thickness">Box lines thickness</param>
#define DEBUG_BOX_ASCT(at, size, color, thickness) if (USE_DEBUG) { DrawDebugBox(GetWorld(), at, FVector(size), color, false, -1, 0, thickness); }
#define DEBUG_POINT if (USE_DEBUG) { DrawDebugPoint(GetWorld(), GetActorLocation(), 1, FColor::Red); }
/// <param name="at">Point location</param>
#define DEBUG_POINT_A(at) if (USE_DEBUG) { DrawDebugPoint(GetWorld(), at, 1, FColor::Red); }
/// <param name="size">Point size</param>
#define DEBUG_POINT_S(size) if (USE_DEBUG) { DrawDebugPoint(GetWorld(), GetActorLocation(), size, FColor::Red); }
/// <param name="color">Point color</param>
#define DEBUG_POINT_C(color) if (USE_DEBUG) { DrawDebugPoint(GetWorld(), GetActorLocation(), 1, color); }
/// <param name="at">Point location</param>
/// <param name="size">Point size</param>
#define DEBUG_POINT_AS(at, size) if (USE_DEBUG) { DrawDebugPoint(GetWorld(), at, size, FColor::Red); }
/// <param name="at">Point location</param>
/// <param name="color">Point color</param>
#define DEBUG_POINT_AC(at, color) if (USE_DEBUG) { DrawDebugPoint(GetWorld(), at, 1, color); }
/// <param name="size">Point size</param>
/// <param name="color">Point color</param>
#define DEBUG_POINT_SC(size, color) if (USE_DEBUG) { DrawDebugPoint(GetWorld(), GetActorLocation(), size, color); }
/// <param name="at">Point location</param>
/// <param name="size">Point size</param>
/// <param name="color">Point color</param>
#define DEBUG_POINT_ASC(at, size, color) if (USE_DEBUG) { DrawDebugPoint(GetWorld(), at, size, color); }
/// <param name="end">Line end location</param>
#define DEBUG_LINE(end) if (USE_DEBUG) { DrawDebugLine(GetWorld(), GetActorLocation(), end, FColor::Red, false, -1, 0, 0); }
/// <param name="end">Line end location</param>
/// <param name="start">Line start location</param>
#define DEBUG_LINE_S(end, start) if (USE_DEBUG) { DrawDebugLine(GetWorld(), start, end, FColor::Red, false, -1, 0, 0); }
/// <param name="end">Line end location</param>
/// <param name="color">Line color</param>
#define DEBUG_LINE_C(end, color) if (USE_DEBUG) { DrawDebugLine(GetWorld(), GetActorLocation(), end, color, false, -1, 0, 0); }
/// <param name="end">Line end location</param>
/// <param name="thickness">Line thickness</param>
#define DEBUG_LINE_T(end, thickness) if (USE_DEBUG) { DrawDebugLine(GetWorld(), GetActorLocation(), end, FColor::Red, false, -1, 0, thickness); }
/// <param name="end">Line end location</param>
/// <param name="start">Line start location</param>
/// <param name="color">Line color</param>
#define DEBUG_LINE_SC(end, start, color) if (USE_DEBUG) { DrawDebugLine(GetWorld(), start, end, color, false, -1, 0, 0); }
/// <param name="end">Line end location</param>
/// <param name="start">Line start location</param>
/// <param name="thickness">Line thickness</param>
#define DEBUG_LINE_ST(end, start, thickness) if (USE_DEBUG) { DrawDebugLine(GetWorld(), start, end, FColor::Red, false, -1, 0, thickness); }
/// <param name="end">Line end location</param>
/// <param name="color">Line color</param>
/// <param name="thickness">Line thickness</param>
#define DEBUG_LINE_CT(end, color, thickness) if (USE_DEBUG) { DrawDebugLine(GetWorld(), GetActorLocation(), end, color, false, -1, 0, thickness); }
/// <param name="end">Line end location</param>
/// <param name="start">Line start location</param>
/// <param name="color">Line color</param>
/// <param name="thickness">Line thickness</param>
#define DEBUG_LINE_SCT(end, start, color, thickness) if (USE_DEBUG) { DrawDebugLine(GetWorld(), start, end, color, false, -1, 0, thickness); }
#define DEBUG_CAMERA if (USE_DEBUG) { DrawDebugCamera(GetWorld(), GetActorLocation(), GetActorRotation(), 80, 1, FColor::White); }
/// <param name="at">Camera location</param>
#define DEBUG_CAMERA_A(at) if (USE_DEBUG) { DrawDebugCamera(GetWorld(), at, GetActorRotation(), 80, 1, FColor::White); }
/// <param name="rotation">Camera rotation</param>
#define DEBUG_CAMERA_R(rotation) if (USE_DEBUG) { DrawDebugCamera(GetWorld(), GetActorLocation(), rotation, 80, 1, FColor::White); }
/// <param name="fov">Camera field of view</param>
#define DEBUG_CAMERA_F(fov) if (USE_DEBUG) { DrawDebugCamera(GetWorld(), GetActorLocation(), GetActorRotation(), fov, 1, FColor::White); }
/// <param name="color">Camera lines color</param>
#define DEBUG_CAMERA_C(color) if (USE_DEBUG) { DrawDebugCamera(GetWorld(), GetActorLocation(), GetActorRotation(), 80, 1, color); }
/// <param name="at">Camera location</param>
/// <param name="rotation">Camera rotation</param>
#define DEBUG_CAMERA_AR(at, rotation) if (USE_DEBUG) { DrawDebugCamera(GetWorld(), at, rotation, 80, 1, FColor::White); }
/// <param name="at">Camera location</param>
/// <param name="fov">Camera field of view</param>
#define DEBUG_CAMERA_AF(at, fov) if (USE_DEBUG) { DrawDebugCamera(GetWorld(), at, GetActorRotation(), fov, 1, FColor::White); }
/// <param name="at">Camera location</param>
/// <param name="color">Camera lines color</param>
#define DEBUG_CAMERA_AC(at, color) if (USE_DEBUG) { DrawDebugCamera(GetWorld(), at, GetActorRotation(), 80, 1, color); }
/// <param name="rotation">Camera rotation</param>
/// <param name="fov">Camera field of view</param>
#define DEBUG_CAMERA_RF(rotation, fov) if (USE_DEBUG) { DrawDebugCamera(GetWorld(), GetActorLocation(), rotation, fov, 1, FColor::White); }
/// <param name="rotation">Camera rotation</param>
/// <param name="color">Camera lines color</param>
#define DEBUG_CAMERA_RC(rotation, color) if (USE_DEBUG) { DrawDebugCamera(GetWorld(), GetActorLocation(), rotation, 80, 1, color); }
/// <param name="fov">Camera field of view</param>
/// <param name="color">Camera lines color</param>
#define DEBUG_CAMERA_FC(fov, color) if (USE_DEBUG) { DrawDebugCamera(GetWorld(), GetActorLocation(), GetActorRotation(), fov, 1, color); }
/// <param name="at">Camera location</param>
/// <param name="rotation">Camera rotation</param>
/// <param name="fov">Camera field of view</param>
#define DEBUG_CAMERA_ARF(at, rotation, fov) if (USE_DEBUG) { DrawDebugCamera(GetWorld(), at, rotation, fov, 1, FColor::White); }
/// <param name="at">Camera location</param>
/// <param name="rotation">Camera rotation</param>
/// <param name="color">Camera lines color</param>
#define DEBUG_CAMERA_ARC(at, rotation, color) if (USE_DEBUG) { DrawDebugCamera(GetWorld(), at, rotation 80, 1, color); }
/// <param name="rotation">Camera rotation</param>
/// <param name="fov">Camera field of view</param>
/// <param name="color">Camera lines color</param>
#define DEBUG_CAMERA_RFC(rotation, fov, color) if (USE_DEBUG) { DrawDebugCamera(GetWorld(), GetActorLocation(), rotation, fov, 1, color); }
/// <param name="at">Camera location</param>
/// <param name="rotation">Camera rotation</param>
/// <param name="fov">Camera field of view</param>
/// <param name="color">Camera lines color</param>
#define DEBUG_CAMERA_ARFC(at, rotation, fov, color) if (USE_DEBUG) { DrawDebugCamera(GetWorld(), at, rotation, fov, 1, color); }
/// <param name="end">Arrow end location</param>
#define DEBUG_ARROW(end) if (USE_DEBUG) { DrawDebugDirectionalArrow(GetWorld(), GetActorLocation(), end, 8, FColor::Red, false, -1, 0, 0); }
/// <param name="end">Arrow end location</param>
/// <param name="begin">Arrow start location</param>
#define DEBUG_ARROW_B(end, begin) if (USE_DEBUG) { DrawDebugDirectionalArrow(GetWorld(), begin, end, 8, FColor::Red, false, -1, 0, 0); }
/// <param name="end">Arrow end location</param>
/// <param name="size">Arrow size</param>
#define DEBUG_ARROW_S(end, size) if (USE_DEBUG) { DrawDebugDirectionalArrow(GetWorld(), GetActorLocation(), end, size, FColor::Red, false, -1, 0, 0); }
/// <param name="end">Arrow end location</param>
/// <param name="color">Arrow color</param>
#define DEBUG_ARROW_C(end, color) if (USE_DEBUG) { DrawDebugDirectionalArrow(GetWorld(), GetActorLocation(), end, 8, color, false, -1, 0, 0); }
/// <param name="end">Arrow end location</param>
/// <param name="thickness">Arrow thickness</param>
#define DEBUG_ARROW_T(end, thickness) if (USE_DEBUG) { DrawDebugDirectionalArrow(GetWorld(), GetActorLocation(), end, 8, FColor::Red, false, -1, 0, thickness); }
/// <param name="end">Arrow end location</param>
/// <param name="begin">Arrow start location</param>
/// <param name="size">Arrow size</param>
#define DEBUG_ARROW_BS(end, begin, size) if (USE_DEBUG) { DrawDebugDirectionalArrow(GetWorld(), begin, end, size, FColor::Red, false, -1, 0, 0); }
/// <param name="end">Arrow end location</param>
/// <param name="begin">Arrow start location</param>
/// <param name="color">Arrow color</param>
#define DEBUG_ARROW_BC(end, begin, color) if (USE_DEBUG) { DrawDebugDirectionalArrow(GetWorld(), begin, end, 8, color, false, -1, 0, 0); }
/// <param name="end">Arrow end location</param>
/// <param name="begin">Arrow start location</param>
/// <param name="thickness">Arrow thickness</param>
#define DEBUG_ARROW_BT(end, begin, thickness) if (USE_DEBUG) { DrawDebugDirectionalArrow(GetWorld(), begin, end, 8, FColor::Red, false, -1, 0, thickness); }
/// <param name="end">Arrow end location</param>
/// <param name="size">Arrow size</param>
/// <param name="color">Arrow color</param>
#define DEBUG_ARROW_SC(end, size, color) if (USE_DEBUG) { DrawDebugDirectionalArrow(GetWorld(), GetActorLocation(), end, size, color, false, -1, 0, 0); }
/// <param name="end">Arrow end location</param>
/// <param name="size">Arrow size</param>
/// <param name="thickness">Arrow thickness</param>
#define DEBUG_ARROW_ST(end, size, thickness) if (USE_DEBUG) { DrawDebugDirectionalArrow(GetWorld(), GetActorLocation(), end, size, FColor::Red, false, -1, 0, thickness); }
/// <param name="end">Arrow end location</param>
/// <param name="color">Arrow color</param>
/// <param name="thickness">Arrow thickness</param>
#define DEBUG_ARROW_CT(end, color, thickness) if (USE_DEBUG) { DrawDebugDirectionalArrow(GetWorld(), GetActorLocation(), end, 8, color, false, -1, 0, thickness); }
/// <param name="end">Arrow end location</param>
/// <param name="begin">Arrow start location</param>
/// <param name="size">Arrow size</param>
/// <param name="color">Arrow color</param>
#define DEBUG_ARROW_BSC(end, begin, size, color) if (USE_DEBUG) { DrawDebugDirectionalArrow(GetWorld(), begin, end, size, color, false, -1, 0, 0); }
/// <param name="end">Arrow end location</param>
/// <param name="begin">Arrow start location</param>
/// <param name="size">Arrow size</param>
/// <param name="thickness">Arrow thickness</param>
#define DEBUG_ARROW_BST(end, begin, size, thickness) if (USE_DEBUG) { DrawDebugDirectionalArrow(GetWorld(), begin, end, size, FColor::Red, false, -1, 0, thickness); }
/// <param name="end">Arrow end location</param>
/// <param name="size">Arrow size</param>
/// <param name="color">Arrow color</param>
/// <param name="thickness">Arrow thickness</param>
#define DEBUG_ARROW_SCT(end, size, color, thickness) if (USE_DEBUG) { DrawDebugDirectionalArrow(GetWorld(), GetActorLocation(), end, size, color, false, -1, 0, thickness); }
/// <param name="end">Arrow end location</param>
/// <param name="begin">Arrow start location</param>
/// <param name="size">Arrow size</param>
/// <param name="color">Arrow color</param>
/// <param name="thickness">Arrow thickness</param>
#define DEBUG_ARROW_BSCT(end, begin, size, color, thickness) if (USE_DEBUG) { DrawDebugDirectionalArrow(GetWorld(), begin, end, size, color, false, -1, 0, thickness); }
#pragma endregion

#pragma region SUBSYSTEMS
#define SUBSYSTEM(type) GetWorld()->GetGameInstance()->GetSubsystem<type>();
#define SUBSYSTEM_V(name, type) TObjectPtr<type> name = GetWorld()->GetGameInstance()->GetSubsystem<type>();
#pragma endregion

#pragma region DEFAULT_SUBOBJECTS
#define CREATE_SPRINGCAM(springArmVar, camVar)\
	springArmVar = CreateDefaultSubobject<USpringArmComponent>(#springArmVar);\
	camVar = CreateDefaultSubobject<UCameraComponent>(#camVar);\
	springArmVar->SetupAttachment(RootComponent);\
	camVar->SetupAttachment(springArmVar);
#pragma endregion

#pragma region INPUTS
#define LOCAL_INPUTS GetWorld()->GetFirstPlayerController()->GetLocalPlayer()->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
#define LOCAL_INPUTS_V(name) TObjectPtr<UEnhancedInputLocalPlayerSubsystem> name = GetWorld()->GetFirstPlayerController()->GetLocalPlayer()->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
#define CAST_INPUTS Cast<UEnhancedInputComponent>(GetWorld()->GetFirstPlayerController()->InputComponent);
#define CAST_INPUTS_V(name) TObjectPtr<UEnhancedInputComponent> name = Cast<UEnhancedInputComponent>(GetWorld()->GetFirstPlayerController()->InputComponent);
#define INIT_MAPPING(mappingVar)\
	LOCAL_INPUTS_V(_inputSystem);\
	if (!_inputSystem) return;\
	_inputSystem->AddMappingContext(mappingVar, 0);
#pragma endregion