#include "unknown_11c920.h"
#include "slot_handler.h"
#include "globals.h"
#include "squads.h"
// @flags /O2 /Gr

struct s_1c7bb0
{
 byte field_0[2];
 char field_2;
 byte field_3[0x28 - 3];
 short field_28;
 byte field_2a[0x7e - 0x2a];
 short field_7e;
 byte field_80[0x98 - 0x80];
};
bool function_204390(long squad_index);
bool actor_update_bsp_locations(long actor_index);
void function_203ed0(long actor_index, bool keep_count);
void function_1e22d0(long actor_index, bool conditional);
void function_203cc0(long squad_index);
bool function_1e13f0(long actor_index);
void function_203fb0(long actor_index);
void function_203d70(long actor_index, short squad_index, bool keep_team);
void function_295e60(short arg_0);
void function_210280();
void function_203f60(long actor_index);
void function_292f10();

struct s_squad_iterator_1c7bb0
{
 byte *squad;
 s_record_pool_iterator records;
 long squad_index;
};

PRIVATE __forceinline bool function_1c7bb1(s_squad_iterator_1c7bb0 *arg_0)
{
 arg_0->squad = NULL;
 if (g_4f55d0->active)
 {
  arg_0->squad = data_iterator_next_calling(&arg_0->records);
  arg_0->squad_index = arg_0->records.datum_index & 0xffff;
 }
 return arg_0->squad != NULL;
}

// score 164 (was 164): frame 0x28 agrees; separate pool/iterator residency, early null and successor EBP remain.
// Frame 0x28 agrees; separate pool/iterator homes, early null publication and successor EBP remain.
// Earlier: Frame 0x28 agrees; separate pool/iterator homes, null timing and successor residency remain.
// frame 0x28 agrees; separate pool/iterator homes,
// frame 0x28 agrees; pool/iterator separation, null timing and successor EBP remain.
// null-result timing and actor-successor residency remain. Inactive early exit
// 164; native flag mask 164; successful inner-update continue 164; pointer-result
// for loop 275; early-exit/mask/continue combination 164.
// Initialized iterator 164; direct iterator index 164; unsigned squad index
// 164; wider inner actor-pointer scope 164; timestamp before active clear 165.
// Frame 0x28 agrees; separate pool homes and iterator/actor lifetimes differ.
// Native record iterator 222; long partition index 163; full actor view 164; outer actor workspace
// 164; ineligible-first branch 171.
// Cached pool 197; role names 164; cached active state 193; nested eligibility 164; inactive
// continue 164; direct datum 164; unsigned successor 164.
// Native record iterator 222; long partition index 163; full actor view 164; outer actor workspace 164; ineligible-first branch 171.
// Cached pool 197; role names 164; cached active state 193; nested eligibility 164; inactive continue 164; direct datum 164; unsigned successor 164.
// traversal phase lifetimes do not recover separate pool
// Earlier: traversal phase lifetimes do not recover separate pool
// storage or the actor successor register. Squad/actor/both phase scopes 164/164/164;
// squad/both scopes with actor for-loop 164/164; squad/both scopes with read-only
// first acquisition 164/164; both scopes with read-only acquisition and for-loop 164.
// Actor-next call alone 234; unsigned-word squad index 230; iterator index initialized first 164;
// active count before timestamp 166; nested source-squad validation 164; per-squad pool observation
// 231.
// Ordinary private next 281; private next out of line 281; separate reacquired actor 164;
// closed initial-actor scope 164; ordinary private next/separate reacquired actor 281.
// Private step byte/signed-byte/short/long results 164 each; inactive index initialization 164;
// inactive index with byte/short/long results 164 each.
// begin expansion 164; actor next expansion 164; actor accessor expansion 164; pool next expansion
// 164; actor iterator expansion 164; actor next accessor expansion 164; begin pool expansion 164;
// all shared expansions 164. Separate pool residency, early null publication and successor EBP
// remain.
// Iterator before entry guard 164; unsigned partition word 164; native actor iterator
// initializer 206; active count before both actor stores 166; Boolean completion-first step 165.
// Round 112: Typed squad result 164; native record-step call 252; shared datum step expanded 267;
// active-aware shared step 240; native datum initialization 252.
// Existing iterator member orders datum/index/records, records/datum/index, records/index/datum,
// index/datum/records and index/records/datum each 164; original layout restored.
// Separate inline/noinline declarations for eligibility, location update, detach, actor test, attach, transfer, partition update and final update each 164. All eight original declarations and both traversals restored.
// @retail 0x1c7bb0
void function_1c7bb0()
{
 if (g_4f55d0->active)
 {
  short local_0 = g_4686c4;
  s_squad_iterator_1c7bb0 local_1;
  byte *datum;
  local_1.records.data = g_51e9d8;
  local_1.records.index = NONE;
  while (function_1c7bb1(&local_1))
  {
   datum = local_1.squad;
   long local_2 = local_1.squad_index;
   if (function_204390(local_2))
   {
    ((s_1c7bb0 *)g_51e9d8->data)[local_2 & 0xffff].field_7e = (short)local_0;
    s_squad_actor_iterator local_4;
    squad_actors_begin(&local_4, local_2);
    s_actor_datum *local_6;
    while ((local_6 = squad_actors_next(&local_4)) != NULL)
    {
     if (!actor_update_bsp_locations(local_4.actor_index))
     {
      *(long *)((byte *)local_6 + 0x34) = local_6->squad_index;
      function_203ed0(local_4.actor_index, false);
      function_203f60(local_4.actor_index);
     }
    }
   }
   else
    ((s_1c7bb0 *)g_51e9d8->data)[local_2 & 0xffff].field_7e = NONE;
   if (((s_1c7bb0 *)datum)->field_2 < 0)
   {
    ((s_1c7bb0 *)g_51e9d8->data)[local_2 & 0xffff].field_28 = 0;
    function_203cc0(local_2);
   }
  }
  long local_4 = g_4f55d0->unknown14;
  while (local_4 != NONE)
  {
   long local_5 = local_4;
   s_actor_view *local_6 = actor_get(local_5);
   local_4 = local_6->unknown020;
   if (function_1e13f0(local_5) && actor_update_bsp_locations(local_5))
   {
    long local_7 = *(long *)((byte *)local_6 + 0x34);
    if (local_7 != NONE && ((s_1c7bb0 *)g_51e9d8->data)[local_7 & 0xffff].field_7e == (short)local_0)
    {
     function_203fb0(local_5);
     function_203d70(local_5, (short)*(long *)((byte *)local_6 + 0x34), true);
    }
   }
   local_6 = actor_get(local_5);
   if (local_6->unknown009)
   {
    local_6->unknown009 = false;
    *(long *)((byte *)local_6 + 0x10) = g_510c54->game_time;
    --*(short *)((byte *)g_4f55d0 + 0x36a);
   }
  }
  function_295e60(local_0);
  function_210280();
  function_292f10();
 }
}
