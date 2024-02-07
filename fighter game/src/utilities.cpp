#include <utilities.h>

Animations::Animations()
{
    idleAnim[0] = {64, 64, 64, 64};
    idleAnim[1] = {264, 64, 64, 64};
    idleAnim[2] = {464, 64, 64, 64};
    idleAnim[3] = {664, 64, 64, 64};
    idleAnim[4] = {864, 64, 64, 64};
    idleAnim[5] = {1064, 64, 64, 64};
    idleAnim[6] = {1264, 64, 64, 64};
    idleAnim[7] = {1464, 64, 64, 64};

    moveAnim[0] = {64, 64, 64, 64};
    moveAnim[1] = {264, 64, 64, 64};
    moveAnim[2] = {464, 64, 64, 64};
    moveAnim[3] = {664, 64, 64, 64};
    moveAnim[4] = {864, 64, 64, 64};
    moveAnim[5] = {1064, 64, 64, 64};
    moveAnim[6] = {1264, 64, 64, 64};
    moveAnim[7] = {1464, 64, 64, 64};

    attack1Anim[0] = {64, 64, 64, 64};
    attack1Anim[1] = {264, 64, 64, 64};
    attack1Anim[2] = {464, 64, 64, 64};
    attack1Anim[3] = {664, 64, 64, 64};
    attack1Anim[4] = {864, 64, 128, 64};
    attack1Anim[5] = {1064, 64, 128, 64};

    attack2Anim[0] = {64, 64, 64, 64};
    attack2Anim[1] = {264, 64, 64, 64};
    attack2Anim[2] = {464, 64, 64, 64};
    attack2Anim[3] = {664, 64, 64, 64};
    attack2Anim[4] = {864, 64, 128, 64};
    attack2Anim[5] = {1064, 64, 128, 64};
}