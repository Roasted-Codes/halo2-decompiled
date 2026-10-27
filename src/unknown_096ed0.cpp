#include "unknown_11c920.h"
#include <xtl.h>
#include "globals.h"
#include "unknown_08b110.h"
#include "unknown_096ed0.h"
#include <stdlib.h>
#include <string.h>

// @flags /O2 /arch:SSE /Gr

long replication_table_get_chain(s_handle_peers *peers, long handle, long *handles);
long replication_table_find_in_chains(s_handle_peers *peers, long *handles, long handle);
void replication_table_release(s_handle_peers *peers, long handle);
void replication_table_release_chain(s_handle_peers *peers, long count, long const *handles);

// score 217 (was 217): Frame 0x48 agrees; receiver EDI/EBP and callback/output/blocked homes remain.
// Earlier 217 from 217: Frame 0x48 agrees; receiver and aggregate/blocked homes remain.
// Earlier 217 from 217: frame 0x48 agrees; receiver EDI/EBP and count,
// priority, size and blocked homes remain. Both redundant count guards removed
// 249; separate native arrays 249; distinct counter names 249; result-home names
// 249; arrays and counter names 249; pending-only guard 242; active-only 220.
// Earlier 217 from 217: Frame 0x48 agrees; receiver/output-slot/priority homes remain. Active priority result 228; mutable cursor 250; native entry/peer/both arrays 236/266/238; shared handle buffer 220; linked for 217; query enum 217; cursor plus priority 259; unmasked arm first 216.
// Frame 0x48 agrees; receiver EDI/EBP and query/blocked homes remain.
// Frame 0x48 agrees; receiver/output-slot/priority homes remain. Active priority result 228; mutable cursor 250; native entry/peer/both arrays 236/266/238; shared handle buffer 220; linked for 217; query enum 217; cursor plus priority 259; unmasked arm first 216.
// State snapshot 217; direct handled states 247; default chain count 238;
// invalid-priority-first arms 221; state/default/arm combination 238.
// Entry-scope guarded arrays 217; shared blocked workspace 217; shared chain
// index 217; shared callback outputs 224; all-ready predicate 220.
// Priority/size/both before pending lookup 221/218/221; active priority/size/both 217/217/217;
// both priorities/all four early 221/221.
// Remaining capacity 262; failed-query counts 239; size accumulation first 229;
// separate chain size 239; capacity/count/size combination 272.
// Pending/active/both counted while 217/217/294; pending/active unsigned chain index 217/217; shared dispatch and chain aggregation 340.
// Round 111: Positive pending/active/both equality termination 217/217/217; active state first 253; Boolean-OR blocked reduction 264.
// Pending/active/both separate chain lengths 219/219/221;
// pre-query peer flags 229; flags plus separate lengths 254.
// Pending/active/both callback outputs before traversal 217/217/217; both with guarded
// output cursor 250; both with emitted-count output indexing 250 (fast); all restored.
// Guarded aggregate priority/size/emitted-count/query-count names and all four together
// 217/217/217/217/217; receiver and callback-output homes remain.
// Round 115: Guarded distinct indices 217; separate blocked names 217; separate callback-output names 217; aggregate declarations first 217; guarded index/blocked names together 217. Opening body restored.
// Pending/active/both invalid-query continues 229/217/229; zero-state exit 217; output-failure exit 217; initialized handle arrays 297; pending/active selector after lookup 219/217. Receiver and callback/output/blocked homes remain.
// Disabled-entry exit 239; empty-list exit 239; both admission exits with later count 246; those
// exits with advancing cursor 244; those exits with active zero-priority join 243. All reach 814
// bytes but regress.
// Round 357: Simple pending/masked-active/both arms first 248/216/246; all query kinds
// after their queries 275; single-handle counts after callbacks 275. Opening body restored.
// Round 165: Pending/active/both byte blocked predicates 217/217/217;
// pending/active/both dword 247/228/247; mixed dword/byte and byte/dword 247/228.
// Original Boolean predicates, all guards and executable body restored.
// Round 165 follow-up: Unsigned handle/link/both domains 217/217/217; readonly
// entry/peer/both views 217/217/217; unsigned handle with both readonly views 217;
// all domains/views 217. Original signed locals and mutable views restored.
// Enabled/nonempty count initialization 230/219; narrow pending/active array names
// 217/217; pending-before-ready/active-before-waiting names 217/217; enabled count
// with pending-before-ready 230; nonempty count with active-before-waiting 219.
// Callback priority/size names before handle homes, pending/active combinations
// and after-handle query names: 217 each; receiver and callback homes remain.
// Round 234: Native state dispatch, either case order, with original pointers,
// entry reference, peer reference and both references: 244 each (816 bytes).
// Original guarded callback/output graph and executable body restored.
// Native state with direct entry/entry-plus-peer/peer fields 236/238/266; native flags
// with direct entry/peer 239/229; both snapshots with direct entry/entry-plus-peer/peer
// 239/239/229. Original entry/peer cursors, field reads and callback/output homes restored.
// Round 188: Chain-query inline/noinline/forceinline/inline-out-of-line declarations, then each
// with native word state observed once:
// 217,217,217,217,217,217,217,217 fast; reduced control 217, full 217. Original executable source restored.
// Round 191: Native two-use payload mask at active gate, with original/cursor/
// conditional size/both output forms 217/250/214/244; before state selection,
// consistently serving applicable callbacks, 217/250/214/244. Three-point best
// restored; original field observations, output graph and executable body restored.
// @retail 0x98150
long c_handle_table_450cd0::v1(long a1, long max_count, void *output)
{
	long count = 0;
	if (unknown09)
	{
		long index = unknown5024;
		if (index != NONE)
		{
			while (index != NONE && count < max_count)
			{
				s_handle_entry *entry = &entries[index];
				if (entry->state)
				{
					long handle = entry->handle;
					s_handle_peer *peer = &table->peers[handle & 0x3ff];
					long type;
					long handles_count;
					real priority;
					long size;
					if (entry->state == 1)
					{
						if (peer->flags & 8)
						{
							long handles[4];
							bool blocked = false;
							type = 3;
							handles_count = replication_table_get_chain(table, handle, handles);
							priority = 0.0f;
							size = 0;
							if (handles_count <= 0)
								goto next;
							for (long i = 0; i < handles_count; i++)
							{
								real item_priority;
								long item_size;
								table->owner->v3(handles[i], entries[handles[i] & 0x3ff].unknown04, a1, &item_priority, &item_size);
								if (item_priority > 0.0f)
									priority = priority > item_priority ? priority : item_priority;
								else
									blocked = true;
								size += item_size;
							}
							if (blocked)
								priority = 0.0f;
						}
						else
						{
							if (peer->flags & 0x10)
								goto next;
							type = 1;
							handles_count = 1;
							table->owner->v3(handle, entry->unknown04, a1, &priority, &size);
						}
					}
					else if (entry->state == 3)
					{
						if (peer->mask & (1 << shift))
						{
							if (peer->flags & 8)
							{
								long handles[4];
								bool blocked = false;
								type = 4;
								handles_count = replication_table_get_chain(table, handle, handles);
								priority = 0.0f;
								size = 0;
								if (handles_count <= 0)
									goto next;
								for (long i = 0; i < handles_count; i++)
								{
									real item_priority;
									table->owner->v9(handles[i], a1, &item_priority);
									if (item_priority > 0.0f)
										priority = priority > item_priority ? priority : item_priority;
									else
										blocked = true;
								}
								if (blocked)
									goto next;
							}
							else
							{
								if (peer->flags & 0x10)
									goto next;
								type = 2;
								handles_count = 1;
								table->owner->v9(handle, a1, &priority);
								size = 0;
							}
						}
						else
						{
							if (!entry->unknown04)
								goto next;
							type = 5;
							handles_count = 1;
							table->owner->v8(handle, entry->unknown04, entry->unknown0c, a1, &priority, &size);
						}
					}
					else
						goto next;
					if (priority > 0.0f)
					{
						s_entry_450c94 *out = (s_entry_450c94 *)output;
						out->unknown00 = *(long *)unknown04;
						out->index = index;
						out->unknown04 = priority;
						out->unknown0c = type;
						out->size = size + 14 * handles_count + 3;
						if (handles_count > 1)
							out->size += 2;
						output = out + 1;
						count++;
					}
				}
			next:
				index = entry->unknown0a;
			}
		}
	}
	return count;
}

// @retail 0x991d0
bool function_991d0(c_handle_table_450cd0 *self, long handle, long size, void const *data)
{
	long index = handle & 0x3ff;
	bool result = false;
	if (self->entries[index].state)
	{
		long old_handle = self->entries[index].handle;
		long difference = ((dword)handle >> 28) - ((dword)old_handle >> 28) + 16;
		if (difference > 8)
			difference -= 16;
		if ((difference >= 0 && difference < 4) || difference <= -4)
		{
			self->table->owner->v11(old_handle, handle, size, data);
			s_handle_peers *peers = self->table;
			byte flags = peers->peers[old_handle & 0x3ff].flags;
			if ((bool)((flags >> 3) & 1) || (flags & 0x10))
			{
				long handles[4];
				long count;
				if ((bool)((flags >> 3) & 1))
					count = replication_table_get_chain(peers, old_handle, handles);
				else
					count = replication_table_find_in_chains(peers, handles, old_handle);
				for (long i = 0; i < count; i++)
					function_99690(self, handles[i], 0);
				replication_table_release_chain(self->table, count, handles);
			}
			else
			{
				function_99690(self, old_handle, 0);
				replication_table_release(self->table, old_handle);
			}
			result = true;
		}
	}
	else
		result = true;
	return result;
}

/* the release routine retail inlines here (allocation is handle_allocate in the header) */
static inline void free_block(void *block)
{
	long info;
	if (!g_4d87f8->allocator->get_info(block, &info))
		info = NONE;
	allocator_globals_release(g_4d87f8, block);
}

// @retail 0x99820
const char *function_99820()
{
	return "slayer-engine-globals";
}

__declspec(noinline) long function_98480(long handle, c_handle_table_450cd0 *self);

/* the next live handle after `handle` (NONE starts at the first), or NONE;
   retail keeps it out of line in has_pending_entity, which otherwise inlines it */
// @retail 0x98480
long function_98480(long handle, c_handle_table_450cd0 *self)
{
	long i;
	if (handle == NONE)
		i = 0;
	else
		i = (handle & 0x3ff) + 1;
	long result = NONE;
	for (; i < 0x400; i++)
	{
		if (self->entries[i].state == 1 || self->entries[i].state == 2)
		{
			result = self->entries[i].handle;
			break;
		}
	}
	return result;
}

__declspec(noinline) bool function_99640(c_handle_table_450cd0 *self, long handle);

// @retail 0x99640
bool function_99640(c_handle_table_450cd0 *self, long handle)
{
	long index = handle & 0x3ff;
	bool result = false;
	if (index >= 0 && (dword)index < 0x400)
	{
		if (self->entries[index].handle == handle)
			result = !self->table->peers[index].flag2 || (self->entries[index].state == 3 && !self->table->peers[index].flag1);
	}
	return result;
}

// @retail 0x995c0
void function_995c0(c_handle_table_450cd0 *self, long handle)
{
	long index = handle & 0x3ff;
	s_handle_peer *peer = &self->table->peers[index];
	s_handle_entry *entry = &self->entries[index];
	if (self->entries[index].state == 1 && !(self->entries[index].unknown10 & self->entries[index].state))
	{
		function_99690(self, handle, 0);
		self->unknown5038++;
		return;
	}
	if (self->entries[index].state == 1)
		function_99690(self, handle, 3);
	peer->mask |= (word)(1 << self->shift);
	if (entry->state == 3)
	{
		if (entry->unknown04 != 0)
			self->unknown5034--;
		self->unknown503c++;
	}
}
// @retail 0x98ac0
void function_98ac0(c_handle_table_450cd0 *self, long handle)
{
	s_handle_item *item = new s_handle_item;
	long index = handle & 0x3ff;
	if (item != 0)
	{
		item->next = self->node->items;
		self->node->items = item;
		item->handle = handle;
		item->kind = 1;
	}
	else
		self->unknown0a = 1;
	self->entries[index].unknown10 |= 1;
	function_99690(self, handle, 2);
}

// @retail 0x98b60
void function_98b60(c_handle_table_450cd0 *self, long handle)
{
	s_handle_item *item = new s_handle_item;
	if (item != 0)
	{
		item->next = self->node->items;
		self->node->items = item;
		item->handle = handle;
		item->kind = 2;
	}
	else
		self->unknown0a = 1;
	function_99690(self, handle, 4);
}

// @retail 0x98bf0
void function_98bf0(long handle, c_handle_table_450cd0 *self, dword mask)
{
	s_handle_record *record = new s_handle_record;
	long index = handle & 0x3ff;
	if (record != 0)
	{
		record->next = self->node->records;
		self->node->records = record;
		s_handle_record *found = 0;
		for (s_handle_node *node = self->head; node != 0; node = node->next)
		{
			for (s_handle_record *other = node->records; other != 0; other = other->next)
			{
				if (other->handle == handle)
				{
					found = other;
					break;
				}
			}
		}
		if (found != 0)
			found->link = record;
		record->handle = handle;
		record->mask = mask;
		record->link = 0;
	}
	else
		self->unknown0a = 1;
	self->entries[index].unknown04 &= ~mask;
	self->entries[index].unknown0c = time_now();
	if (self->entries[index].state == 3 && self->entries[index].unknown04 == 0)
		self->unknown5034--;
}
/* ---- the sender state of 0x450d1c (see c_vtable_450d1c in unknown_08b110.h) ---- */
struct s_sender_node;

class c_sender_manager
{
public:
	virtual void v0() = 0;
	virtual void v1() = 0;
	virtual void v2() = 0;
	virtual void v3(s_sender_node *node) = 0;
};

struct s_sender_node
{
	byte unknown00[0x18];
	void *block;
	byte unknown1c[4];
	dword active_mask;
	dword done_mask;
	s_sender_node *next;
};

struct s_sender_owner
{
	byte unknown00[4];
	c_sender_manager *manager;
	byte unknown08[0x40];
	long count;
	s_sender_node *head;
};

struct s_sender_link
{
	s_sender_node *node;
	s_sender_link *next;
};

struct s_sender_request
{
	long key;
	s_sender_link *links;
	s_sender_request *next;
};

struct s_sender
{
	byte unknown00[0xc];
	long player;
	s_sender_request *requests;
	long request_count;
	s_sender_owner *owner;
	long unknown1c;
	long pending;
	long unknown24;
};

static __forceinline void function_96ed1(void *arg_0)
{
	long local_0;
	if (!g_4d87f8->allocator->get_info(arg_0, &local_0))
		local_0 = NONE;
	c_allocator *local_1 = g_4d87f8->allocator;
	s_allocator_globals *local_2 = g_4d87f8;
	local_1->release(arg_0, NONE);
	if (arg_0 != 0)
		local_2->count--;
}

// @retail 0x96ed0
void function_96ed0(s_sender *self)
{
	s_sender_request *request = self->requests;
	self->requests = 0;
	if (request != 0)
	{
		do
		{
			s_sender_link *link = request->links;
			s_sender_request *next_request = request->next;
			if (link != 0)
			{
				do
				{
					s_sender_node *node = link->node;
					s_sender_link *next = link->next;
					node->done_mask &= ~(1 << self->player);
					free_block(link);
					link = next;
				}
				while (link != 0);
			}
			free_block(request);
			request = next_request;
		}
		while (request != 0);
	}

	s_sender_node *node = self->owner->head;
	if (node != 0)
	{
		do
		{
			s_sender_node *next = node->next;
			dword mask = 1 << self->player;
			if (node->active_mask & mask)
			{
				s_sender_owner *owner = self->owner;
				node->active_mask &= ~mask;
				if (node->active_mask == 0)
				{
					owner->manager->v3(node);

					/* 0x89e70 and 0x89eb0, which retail inlines here */
					s_sender_node **link = &owner->head;
					if (*link != 0)
					{
						do
						{
							s_sender_node *current = *link;
							if (current == node)
							{
								*link = node->next;
								break;
							}
							link = &current->next;
						}
						while (*link != 0);
					}
					owner->count--;
					if (node->block != 0)
						function_96ed1(node->block);
					free_block(node);
				}
			}
			node = next;
		}
		while (node != 0);
	}
	self->pending = 0;
	self->unknown1c = 0;
	self->unknown24 = 0;
}
/* ---- the sorting of 0x97ab0 ---- */
struct s_priority_entry_raw { long v[5]; };

struct s_priority_entry
{
	long child;
	real priority;
	long size;
	long unknown0c;
	long index;
};

// @retail 0x97a80
int __cdecl function_97a80(const void *a, const void *b)
{
	real difference = ((const s_priority_entry *)b)->priority - ((const s_priority_entry *)a)->priority;
	if (difference > 0.0f)
		return 1;
	if (difference < 0.0f)
		return -1;
	return 0;
}
/* retail inlines the stream initialization here */
static inline void stream_initialize(s_bitstream *stream, void *buffer, long size, long mode)
{
	stream->mode = mode;
	stream->data = (byte *)buffer;
	stream->size_in_bytes = size;
	stream->unknown08 = 1;
	memset(stream->data, 0, stream->size_in_bytes);
	stream->bit_position = 0;
	stream->checkpoint_count = 0;
	stream->error = false;
	if (stream->mode == 1)
	{
		stream->unknown2c = 0;
		stream->unknown30 = 0;
	}
	else if (stream->mode == 3 || stream->mode == 4)
	{
		if (function_1959c0(stream, 0x20) == 0x64656267)
			stream->error = true;
		else
		{
			stream->bit_position = 0;
			stream->error = false;
		}
	}
}

/* retail inlines the end of a stream here: its size is rounded up to the
   alignment, and its bits are appended to the output */
static __forceinline void function_97ab1(s_bitstream *arg_0, s_bitstream *arg_1)
{
	long *local_0 = &arg_0->size_in_bytes;
	long local_1 = local_0[3];
	long local_2 = local_0[1];
	long local_3 = (local_1 + 7) / 8;
	local_0[0] = local_3;
	long local_4 = local_3 % local_2;
	if (local_4)
		local_0[0] = local_3 - local_4 + local_2;
	local_0[2] = 2;
	function_1955d0(arg_1, (void *)local_0[-1], local_1);
	arg_1->unknown2c += local_0[10];
	arg_1->unknown30 += local_0[11];
}

// @retail 0x97ab0
bool c_aggregate_450cf4::v4(long a1, s_bitstream *out, long a3, long reserved_bits)
{
	s_priority_entry_raw list_raw[2000];
	s_priority_entry *list = (s_priority_entry *)list_raw;
	dword buffers[3][0x180];
	s_bitstream streams[3];
	long total = 0;
	bool overflowed = false;
	long source_value = source->v0();
	for (long i = 0; i < 3; i++)
	{
		c_handle_table_450cd0 *child = children[i];
		if (child != 0 && child->v0())
			total += child->v1(source_value, 2000 - total, &list[total]);
	}
	qsort(list, total, sizeof(s_priority_entry), function_97a80);
	if (total > 0x100)
		total = 0x100;

	long budget = (out->size_in_bytes << 3) - out->bit_position - reserved_bits;
	long k = 0;
	do
	{
		streams[k].mode = 0;
		streams[k].bit_position = 0;
		streams[k].checkpoint_count = 0;
		streams[k].error = false;
		k++;
	}
	while (k < 3);
	budget -= unknown24;
	for (long i = 0; i < 3; i++)
		stream_initialize(&streams[i], buffers[i], 0x600, 1);

	if (a1 != NONE)
	{
		for (long i = 0; i < total; i++)
		{
			long *local_0 = &list_raw[i].v[1];
			long which = local_0[-1];
			if (local_0[1] <= budget)
			{
				c_handle_table_450cd0 *child = children[which];
				s_bitstream *stream = &streams[which];
				if (child != 0)
				{
					long before = stream->bit_position;
					child->v3(local_0[3], local_0[2], source_value, a1, (long)stream, (stream->size_in_bytes << 3) - before - budget);
					budget += before - stream->bit_position;
					if (budget <= 0)
						break;
				}
			}
			else
				overflowed = true;
		}
	}

	for (long i = 0; i < 3; i++)
	{
		c_handle_table_450cd0 *local_1 = children[i];
		if (local_1)
			local_1->v4(a1, &streams[i]);
	}

	for (long i = 0; i < 3; i++)
	{
		if (children[i] != 0)
			function_97ab1(&streams[i], out);
	}	return overflowed;
}
/* the part of 0x992d0 that points the records of earlier nodes, which referred
   to a record about to be freed, at what that record referred to */
static inline void records_relink(s_handle_node *head, s_handle_node *stop, long handle, s_handle_record *record)
{
	s_handle_node *other = head;
	while (other != 0 && other != stop)
	{
		s_handle_record *candidate = other->records;
		other = other->next;
		for (; candidate != 0; candidate = candidate->next)
		{
			if (candidate->handle == handle && candidate->link == record)
			{
				candidate->link = record->link;
				return;
			}
		}
	}
}

// @retail 0x992d0
void c_handle_table_450cd0::v8(long handle, bool flag)
{
	s_handle_node **head_link = &head;
	s_handle_node **link = &head;
	s_handle_node *node = *link;
	while (node != 0)
	{
		if (node->handle == handle)
		{
			s_handle_record *record = node->records;
			if (record != 0)
			{
				do
				{
					long record_handle = record->handle;
					s_handle_record *next_record = record->next;
					long index = record_handle & 0x3ff;
					s_handle_peer *peer = &table->peers[index];
					if (!flag)
					{
						dword mask = record->mask;
						for (s_handle_node *other = node->next; other != 0; other = other->next)
						{
							for (s_handle_record *candidate = other->records; candidate != 0; candidate = candidate->next)
							{
								if (candidate->handle == record_handle)
									mask &= ~candidate->mask;
							}
						}
						if (mask != 0 && entries[index].unknown04 == 0 && entries[index].state == 3)
						{
							if (!(peer->mask & (1 << shift)))
								unknown5034++;
						}
						entries[index].unknown04 |= mask;
					}
					else
						unknown5030++;
					records_relink(*head_link, node, record_handle, record);
					free_block(record);
					record = next_record;
				}
				while (record != 0);
			}

			s_handle_item *item = node->items;
			if (item != 0)
			{
				do
				{
					long item_handle = item->handle;
					s_handle_item *next_item = item->next;
					long offset = (item_handle & 0x3ff) * sizeof(s_handle_peer);
					s_handle_peer *peer = (s_handle_peer *)((byte *)table->peers + offset);
					if (item->kind == 1)
					{
						if (!flag)
						{
							if (peer->mask & (1 << shift))
								function_99690(this, item_handle, 3);
							else
								function_99690(this, item_handle, 1);
						}
						else
						{
							function_99690(this, item_handle, 3);
							unknown5028++;
						}
					}
					else if (!flag)
						function_99690(this, item_handle, 3);
					else
					{
						function_99690(this, item_handle, 0);
						peer->mask &= ~(1 << shift);
						s_handle_peers *peers = table;
						if (((s_handle_peer *)((byte *)peers->peers + offset))->mask == 0)
						{
							peers->owner->v12(item_handle);
							byte *flags = (byte *)peers->peers + offset;
							*flags &= 0xfe;
						}
						unknown5038++;
					}
					free_block(item);
					item = next_item;
				}
				while (item != 0);
			}

			*link = node->next;
			free_block(node);
			return;
		}
		link = &node->next;
		node = *link;
	}
}
// score 2 (was 154): Retail length and frame agree; case 5 loads the handle table into ECX, ours into EDX.
// Round 73 kept: cleanup slot read at each use, full-width kind, nonzero-kind nesting, indexed
// for loop with cases 1/3 sharing one call, count before the block stores, globals-parameter
// release helper (154 -> 149 -> 26 -> 2). Case 5 forms then: entry pointer 50; reversed handle
// compare 3; first-element/explicit-this/break-first/negated/ternary/long-item/dword-compare 2 each;
// default-2-first 113; unsigned index or items store first 2; count declared first 4; data before
// info 2; produced before memset 7; in-helper allocator/globals locals 26.
// Native kind 211; role-named scalars 204; shared callback arm 222;
// library descriptor/payload copies 204; pretested item while 220.
// Unsigned native item total 204; joint count/error item guard 220; direct local output cursor 211;
// pair-pointer cleanup 206; payload-before-info declaration 204.
// Round 132: count after block publication 193 plain kept (688/692 bytes); frame 0x98,
// count/kind/callback homes still differ. Entry decision/common exit/path results 271/248/206;
// native-kind pairs 271/236/223; native kind plus count publication 204; both cursors after
// publication 208; indexed post-publication output 212.
// Count-bearing descriptor aggregate 208; update case first 211; persistent descriptor 204;
// native high nibble 207; total-only lexical order 204.
// Count-first declarations 205; entry-scope advancing cursor 217; produced before descriptor clear
// 205; existing release helper 207; native kind with both initialization changes 212.
// Round 111: Header error recheck removed 206; do-while error continuation 272; persistent native payload 204; persistent produced total 204; update error default first 204.
// Item cursor 221; paired callback cursors 185 plain kept; all descriptor cursors 193;
// unsigned error 193; word kind 204; default first 193; reverse cases 211;
// all cursors with full-width kind 204.
// Paired cursors with native kind 203; paired/native kind with pretested for 217.
// Round 157: Range-first byte/native kind 232/198; count-default byte/native 232/218; terminal-test
// count byte/native 214/219; test-count pretested while byte/native 214/215.
// High/low cursor names 185; second cursor declared first 185; descriptor zero
// initializer 186; names/declaration order 185; names/initializer 186;
// declaration order/initializer 186; all three 186; cursor declarations before scalars 185.
// callback-table 251; update-entry 198.
// callback-table-update-entry 219; count-home-names 185.
// callback-table-count-home-names 251; update-entry-count-home-names 198.
// callback-table-update-entry-count-home-names 219; table-before-item-publication 251.
// Round 199: Descriptor-owned item bound, byte kind with indexed/pretested/item-cursor/both forms
// 216/203/181/191; native-kind counterparts 208/205/224/195 (fast). All restored.
// Round 159: Second-only/first-only callback cursors with byte kind 218/218; native kind 219/219;
// second-plus-item/first-plus-item cursors with byte kind 218/218 and native kind 219/219. All 704/692
// bytes, frame 0x9c versus 0x98. Original paired cursors, item indexing, copies and cleanup restored.
// Round 161: Failure-first 193; native kind 208; direct cleanup-array reads 178;
// native kind plus array reads 202; metadata before copies 181; failure-first metadata
// 193; failure-first native metadata 208; failure-first descriptor before index 193.
// Seven/four-point previews rejected by minimum gain; original body restored.
// Shared item/cleanup ordinal 185; with pretested items 222; case-local index 200;
// case-local/pretested 266; native kind 203; native/pretested 217; native/case-local
// 202; all three 217. Opening body restored.
// Round 145: First-array endpoint byte/posttest 157, byte/pretest 250, native/posttest 177,
// native/pretest 186; second-array counterparts 154/249/177/186. On second-array endpoint: enum
// kind 177; shared creation arm 170; enum/shared arm 178; word kind 195.
// Round 149: Second-array endpoint graph: scalar/buffer lexical home masks and entry buffer
// declarations 154 each; range-first byte/native 216/205, default-first 228/221, terminal-produced
// count 210/208; range/default native unsigned count 205/221. Original endpoint and full body
// restored.
// Round 151: Inline reader byte/native 154/177; explicit descriptor/payload copies with each 154/177;
// separate out-of-line reader counterparts 154/177/154/177. Reader contracts and all copies restored.
// @retail 0x98cf0
long c_handle_table_450cd0::v5(dword a1, s_bitstream *stream, long max_blocks, s_handle_block *blocks, long *count_out)
{
	long error = 0;
	long count = 0;
	if (unknown0a)
		error = 2;
	else
	{
		s_handle_block *cursor = blocks;
		do
		{
			dword type = function_1959c0(stream, 3);
			long n;
			if (type >= 6)
			{
				error = 3;
				break;
			}
			if (type != 0)
			{
				if (type > 2 && type <= 4)
				{
					n = function_1959c0(stream, 2) + 2;
					if (n < 1 || n > 4)
					{
						error = 3;
						break;
					}
				}
				else
					n = 1;
			}
			else
				n = 0;
			if (error != 0)
				break;
			if (count >= max_blocks && n > 0)
			{
				error = 3;
				break;
			}
			if (n == 0)
				break;

			s_handle_block_info info;
			s_handle_block_data data;
			memset(&info, 0, sizeof(info));
			info.count = n;
			long produced = 0;
			for (long i = 0; i < n; i++)
			{
				if (error != 0)
					break;
				dword low = function_1959c0(stream, 10);
				dword item = low | ((byte)function_1959c0(stream, 4) << 28);
				long index = item & 0x3ff;
				info.items[i] = item;
				switch (type)
				{
				case 1:
				case 3:
					error = table->owner->v1(item, &info.b[i], &info.c[i], 8, &produced, data.v, stream);
					break;
				case 2:
				case 4:
					break;
				case 5:
					if (entries[index].handle == (long)item && entries[index].state == 3)
						error = table->owner->v6(item, info.c, 8, &produced, data.v, stream);
					else
						error = 2;
					break;
				default:
					error = 3;
					break;
				}
			}

			if (error == 0)
			{
				count++;
				s_handle_block *block = cursor;
				cursor++;
				block->type = type;
				block->index = info.items[0];
				block->info = info;
				block->count = produced;
				block->data = data;
			}
			else
			{
				for (long k = 0; k < produced; k++)
				{
					if (data.v[k * 2 + 1] != 0)
					{
						free_block(data.v[k * 2 + 1]);
						data.v[k * 2 + 1] = 0;
					}
				}
			}
		}
		while (error == 0);
	}
	*count_out = count;
	return error;
}
