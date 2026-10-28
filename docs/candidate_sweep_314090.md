# Constraint candidate sweep

The 2026-10-28 sweep covered the game and Havok inventory on `d377cd5e`,
checked active person claims and 46 open pull requests, and excluded disabled
drafts. It found 1,536 available unmatched functions (1,156,390 retail bytes).
These are inventory candidates, not predictions of successful matches.

The strongest new-work cluster is `0x314090` through `0x3157ff`: constraint
descriptions, field import/export, runtime accessors and callbacks. Most have
no active source. Several constructors and copy routines call already matched
base helpers, making them preferable to repeatedly tuning register-only near
misses. Work begins with those leaves and proceeds toward their callers.

Other leads inspected:

| Candidate | Finding |
| --- | --- |
| `0x31bbd0` | Six unmatched callers, but the existing constructor cannot currently be marked because the generated stand-in instantiates an abstract base. Needs a tooling/type-model solution. |
| `0x31c000` | Three unmatched callers; substantial constructor with multiple vtables and embedded arrays. Requires reconstructing the class hierarchy. |
| `0xd6660`, `0xb9b90` | Each has 22 unmatched callers, but existing differences are instruction scheduling, with several recorded unsuccessful approaches. |
| `0xe4050` | Eighteen unmatched callers; boolean materialization and reuse of constant one remain. Worth a focused control-flow investigation later. |
| `0x2f3030` | 2,287 bytes, score 1; remaining difference is base/index ordering, already extensively attempted. |
| `0x2f4f00`, `0x2f5960` | More than 5 KB together, but remaining x87 operand ordering has substantial attempt history. |
| `0x27dff0`, `0x281b60`, `0x2898b0` | Large shared-inline routines; stack-load ordering differs, and shared edits could disturb matched siblings. |

Analysis uses only this repository and independent examination of the retail
executable. No SDK or retail executable material is contributed.
