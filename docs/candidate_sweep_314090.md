# Constraint candidate sweep

The 2026-10-28 sweep covered the game and Havok inventory on `d377cd5e`,
checked active person claims and 46 open pull requests, and excluded disabled
drafts. It found 1,536 available unmatched functions (1,156,390 retail bytes).
These are inventory candidates, not predictions of successful matches.
Of those, 141 have no active source and 84 of those have no unmatched direct
game/Havok callees. The written candidates comprise 73 scores of 1-2, 291
scores of 3-20 and 1,031 larger differences. This is why the selection moved
beyond the smallest difference scores.

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

## Implemented batch

The full-image checker confirms 31 new matches, covering 1,418 retail bytes,
with no lost matches. All 26 address fields in the new matched functions are
verified; none differs or remains unverified. Initial validation on `d377cd5e`
retained 9,895 game matches. Upstream then incorporated the previous batch's
two matches; validation was repeated against `5156911ab`, retaining all 9,897
game matches. Havok matches increase from 1,181 to 1,212 (11,112 total matches
in scope on the updated base).

| Family | Matched retail addresses |
| --- | --- |
| Ball/socket description and access | `0x314090`, `0x3140a0`, `0x3140c0`, `0x3141b0`, `0x3141c0`, `0x3141f0`, `0x3142f0` |
| Motion limits | `0x314320`, `0x314350`, `0x314360`, `0x314450`, `0x314480`, `0x3144b0`, `0x314580` |
| Spring description and access | `0x314830`, `0x314840`, `0x314860`, `0x314950`, `0x314960`, `0x314980`, `0x3149b0`, `0x314b50` |
| Prismatic description and access | `0x314b80`, `0x314b90`, `0x314cc0`, `0x314d50`, `0x314dd0`, `0x314e00`, `0x314fa0` |
| Contact sizes | `0x3155f0`, `0x315720` |

Two additional first implementations remain unmatched: `0x314bb0` scores 12
(zero/identity-store scheduling) and `0x314cd0` scores 9 (virtual-table load
scheduling). Their source comments document the differences. No register or
instruction-order search was pursued after identifying those limitations.

The shared header replaces duplicate snapshot and motion-limit declarations.
Game callers now use the reconstructed description fields at the same offsets;
nine inert stubs are replaced by real definitions. Compile-time checks cover
snapshot sizes and important runtime offsets. No compiler flags or checker
rules are changed for existing files.
The repository Python suite also passes: 424 passed, 14 skipped (optional
retail/toolchain fixtures and a platform-specific test).

## Follow-up results

All four suggested targets now match in the ordinary full-image check:

| Address | Bytes | Behavior |
| --- | ---: | --- |
| `0x314140` | 101 | Nullable placement construction of a ball/socket description |
| `0x3143e0` | 100 | Nullable placement construction of a motion-limit description |
| `0x3148e0` | 108 | Nullable placement construction of a spring description |
| `0x314650` | 143 | Store the squared half-diagonal of a shape's bounds; store -1 without a shape |

The three existing constructor bodies moved unchanged into
`src/constraint_construction_314140.cpp`, alongside their callbacks. `/O2`
inlines them in the callbacks, and `/GX` produces the retail exception frames.
All three constructors retain their own matches. The radius routine is in
`src/motion_radius_314650.cpp`; `_mm_set_ss` produces the retail half-scale
load without introducing a pointer temporary. The callbacks matched on the
first implementation, and the radius routine on its second compilation.

This adds 452 matched bytes and preserves every previous match. The complete
PR now implements 37 functions: 35 matched (1,870 bytes), with the same two
unmatched implementations documented above. Against `5156911ab`, game matches
remain 9,897 and Havok matches reach 1,216; there are 11,116 total matches in
scope. No checker or compiler-rule changes were needed.

The new matched functions have three automatically verified address fields
and four fields the checker still reports as unverified. Those four were
independently checked against the retail executable: all three generated
handlers dispatch to the same CRT exception handler, their function-info and
single-state unwind metadata agree, and their cleanup instructions agree
apart from the relocated call to an empty placement-delete function. The
radius routine's identity transform agrees with all 64 retail bytes at
`0x461ea0`, including its homogeneous position lane.

The next dependency is `0x314710`, which calls the now-matched radius routine
but still needs the object's virtual-table model. The six concrete joint
constructors should be pursued with their common base `0x31bbd0`, whose
abstract-class stand-in issue remains.
