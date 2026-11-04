# Subsystem map

The executable by area: what each address range does in the game, which file names are known there, how much of it is still unlinked and whether it is held. Pick work here, then claim one file with a draft PR ([AGENTS.md](../AGENTS.md#files-are-the-unit-of-work)).

**Order of work (owner, 2026-11-04).** First the standing PRs are folded into `main`, then the foundation tools and these docs land, then the structure pass splits the large chunks into files. File work (linking, matching, naming) starts on the map that the structure pass produces; until then, use this page to learn the code.

**Snapshot.** Measured on `main` 38935dd (the site's map for that revision, 2026-10-30); the Held column and known files are current to `main` 362450f, which integrated PRs #1216-#1218 (#1220). Ranges are `.text` addresses of target `GN7E69-rev0`, end exclusive. Descriptions come from the strings, module names and inferred names that the files in each range already use; where nobody has read the code yet, the row says so. They are a guide for choosing work, not evidence: a boundary or name still needs its own `evidence.tsv` row.

**Rungs.** Unlinked chunks in the site map (`Candidate` chunks, SDK files and unassigned SDK intervals) in the range, placed by their `.text` start, counted by how many functions still block them: `0` none (100% exact, needs only a boundary decision and a link), `1` one, `2` two or three, `3` four to ten, `4` more than ten. Rung-4 chunks are split into files before anyone works their functions. "Unlinked" is the size of those chunks in KiB (1,024 bytes).

**Held.** Areas reserved for the structure pass or another contributor. Claims of single files are the open draft PRs, not this column: check the PR list before you start.

## Game code (`src/game/`)

NFL Street 2's own code: the front end, game modes, gameplay, replay and the rendering of players and the field. Built with SN ProDG 3.9.3, mostly C++, organised as Tiburon `Module` subclasses (each has `Init`, `Shutdown`, `GetDependencies`, `GetLinks` and `GetName`).

| Range | What it does in the game | Known files | Rungs 0/1/2/3/4 | Unlinked | Held |
| --- | --- | --- | --- | --- | --- |
| 0x800034A0-0x80005668 | Start-up helpers and team creation (team name, logo, team colours) | `cu_80004AF0` | 1/0/1/1/0 | 5 KiB | no |
| 0x80005668-0x8000F870 | Create-a-player: attributes, appearance and gear menus, the shops (Reebok Store, Barbershop, Tattoo Parlor) | `cu_80005668` (create-a-player), `cu_8000A360` (gear menu), `cu_8000DCD8` (shops) | 1/1/0/0/0 | 7 KiB | no |
| 0x8000F870-0x8001BB20 | Roster and team-pick screens; team records and stats in the game database | `cu_8000F870`, `cu_800170E0` | 0/0/0/2/0 | 49 KiB | no |
| 0x8001BB20-0x80023000 | Front-end menus: game type, skill levels, playbook styles, EA Trax, options | front-end gap units (`cu_8001BB20` ...) | 2/1/1/0/0 | 5 KiB | no |
| 0x80023000-0x80025E00 | Save data and display settings (progressive/interlaced prompt), card streaming | `CardStream.cpp`, `ArenaSetup.cpp` | 2/0/0/0/0 | 0 KiB | no |
| 0x80025E00-0x80029500 | Game framework: the `Module` base, one-module files, the main loop, front-end and in-game loops, game state | `Module.cpp`, `Font.cpp`, `Mat.cpp`, `Obj.cpp`, `Res.cpp`, `Tex.cpp`, `Vec.cpp`, `Vpt.cpp`, `MainLoop.cpp`, `FELoop.cpp`, `InGame.cpp`, `GameObjList.cpp`, `TimeScale.cpp`, `GameState.cpp`, `GameVpt.cpp` | 0/0/0/0/0 | 0 KiB | no (all linked; naming still to do) |
| 0x80029500-0x8002B8F8 | Options and player export to the memory card; the viewport (camera stack) manager | `cu_80029500`, `src/engine/vptmanager.cpp` | 0/1/0/0/0 | 5 KiB | no |
| 0x8002B8F8-0x800314E0 | Replay (`REPLAY.C` string), its debug window, the replay event list | `cu_8002B8F8`, `cu_8003108C` | 0/0/1/1/0 | 22 KiB | no |
| 0x800314E0-0x8003877C | Module groups: debug, main front end, system, and about 60 in-game modules registered in one file | `DebugGroup.cpp`, `SystemGroup.cpp`, `Debug.cpp`, `FEDLL.cpp`, `ModuleGroup_80033A5C.cpp`, `ModuleGroup_8003450C.cpp`, `LoadingFEToInGame.cpp` | 0/2/0/0/0 | 17 KiB | no |
| 0x8003877C-0x80056584 | In-game world: players and their bones, object definitions, crowd and big objects, field divots, dynamic colour tables, jersey and number textures, animation state data, path nodes, hotspot moves | `cu_8003877C`, `cu_800400CC`, `cu_80042F54`, `cu_80044F20`, `cu_800478DC`, `cu_8004A2F4`, `cu_80052F54` | 0/4/0/7/2 | 83 KiB | no |
| 0x80056584-0x80068154 | Game modes and story: play setup (4 on 4, street balls), story tasks, NFL draft | `cu_80056584`, `cu_8005D60C`, `cu_80060948` | 1/1/0/1/2 | 52 KiB | no |
| 0x80068154-0x8007342C | Audio direction: music path finder, crowd sound, song selection | `SndgPathfinder.cpp`, `SndgCrowd.cpp`, `cu_80071C3C` | 0/0/0/2/0 | 15 KiB | no |
| 0x8007342C-0x8008B32C | In-game speech start-up, style points and stats, team colour palettes, saved records and tournaments, game-database wrappers, paired-single setup in assembly | `DbColPal.cpp`, `cu_80077A24`, `cu_80081CDC`, `cu_800834CC`, `cu_80088F2C` | 0/6/2/5/0 | 35 KiB | no |
| 0x8008B32C-0x8008E978 | Front-end modules: playbook, celebrations, rumble, player import, loading screens | `FEModules.cpp`, `AnmsCelebration.cpp`, `Celebration.cpp`, `Rumble.cpp`, `Timg.cpp`, `FMCAPPORT.cpp`, `LoadingFE.cpp`, `ModuleGroup_8008CC74.cpp` | 0/0/0/0/0 | 0 KiB | no (all linked) |
| 0x8008E978-0x800CF84C | One 202 KiB chunk of gameplay code: Gamebreaker, post game, animation scripts, defensive play prediction, player abilities, market camera | `cu_8008E978` | 0/0/0/0/1 | 202 KiB | yes: being tested as several files built as one; no function work |
| 0x800CF84C-0x800EFC68 | End-of-play state machine, animation tables, ball and foot handling | `cu_800CF84C`, `cu_800D0D4C`, `cu_800D8A24`, `cu_800DAEE4`, `cu_800E3CC0` | 1/1/2/1/2 | 120 KiB | no |
| 0x800EFC68-0x80125F3C | One 190 KiB chunk of gameplay code that nobody has mapped yet; it uses player bone names (`rwrist`, `lshoulder`). An unreferenced `ASSIGN.C` file-name tag (.data 0x802DAAC4) heads its data, in the same position as `REPLAY.C` in `cu_8002B8F8`, so its original name is probably `ASSIGN.C`; this is inferred from the tag, not yet an evidence row | `cu_800EFC68` | 0/0/0/0/1 | 190 KiB | yes: being tested as several files built as one; no function work |
| 0x80125F3C-0x801485B4 | Game cameras (curve and playback cameras, aspect), ball objects, replay particles | `cu_8012A6B0`, `cu_8013141C`, `cu_8013CD58`, `cu_8013F460`, `cu_80141210` (curve cameras), `cu_801444D8` | 1/6/1/7/3 | 97 KiB | no |
| 0x801485B4-0x801564DC | Mini-games and event modes: 2 Minute Challenge, Crush the Carrier, elimination, Open Field Showdown, Quick Strike | `cu_8014D210`, `cu_80150DFC` | 0/0/0/0/1 | 7 KiB | yes: another contributor |
| 0x801564DC-0x80167A8C | Tutorial lessons; player appearance assembly (body types, heads, accessories); sky | `cu_801564DC` (tutorial), `cu_8015C25C`, `cu_8015D3EC`, `cu_8016014C` | 0/0/1/3/2 | 39 KiB | no |
| 0x80167A8C-0x80181330 | Playbook, team database, ball-strip calls ("Gimme That!"), scramble rules, button mashing | `cu_80167A8C` (playbook), `cu_8016FB10`, `cu_80176F18` (ScrmRule), `cu_8017D0E0` | 0/1/3/1/1 | 53 KiB | no |
| 0x80181330-0x80190A7C | Edit team and edit player screens, save game, memory card screens, widescreen aspect, story team | `cu_80181330`, `cu_80187AD4`, `cu_80188E98` (aspect and camera set-up), `cu_8018B0BC` | 1/5/1/2/0 | 27 KiB | no |
| 0x80190A7C-0x801A1400 | Animation extension and bit stream, memory card messages, particle and field-line rendering, ball model, on-field markers; system modules | `animextn.cpp`, `bitstream.cpp`, `cu_80191948`, `cu_801962CC`, `cu_8019AD24`, `cu_801A0088`, `FileIO.cpp`, `GRender.cpp`, `GLIB.cpp`, `Render.cpp`, `Snd.cpp`, `Sys.cpp` | 1/1/4/3/0 | 31 KiB | no |
| 0x801A1400-0x801AA640 | Player head, face and hair rendering, body parts, simple shadows, model and crowd rendering | `cu_801A14D8`, `cu_801A4AD4`, `cu_801A8620` | 0/1/1/2/0 | 21 KiB | no |

## Libraries and EA engine (`src/engine/`, `src/Common/`)

Tiburon's shared engine, written mostly in C with lowercase file names; NASCAR 2005's file list matches much of it by size and order. Built with SN ProDG.

| Range | What it does in the game | Known files | Rungs 0/1/2/3/4 | Unlinked | Held |
| --- | --- | --- | --- | --- | --- |
| 0x801AA640-0x801AE3E4 | SN Systems runtime: debugger stub, exception vectors, DVD helpers | `cu_801AA640` (libsn runtime), `cu_801AD424`, `cu_801AD57C` | 0/1/1/1/1 | 15 KiB | no |
| 0x801AE3E4-0x801B2AD4 | Speech playback runtime (`SPCHAUTHOR` block) | `cu_801AE3E4` | 0/0/0/0/1 | 18 KiB | no |
| 0x801B2AD4-0x801B9D00 | Interactive music runtime (`PATHAUTHOR` block) | `cu_801B2AD4`, `cu_801B8C18` | 0/0/0/1/1 | 29 KiB | no |
| 0x801B9D00-0x801C1D84 | Animation C library | `anim.c`, `animtran.c`, `animTexLib.c`, `llanimtexlib.c`, `cu_801BA2A8`, `cu_801BC65C`, `cu_801BF090` ... | 1/3/4/2/0 | 20 KiB | no |
| 0x801C1D84-0x801D134C | Engine core: C library helpers, keyframe evaluation, module nodes, matrix library | `ctype.c`, `camera.c`, `camfocus.c`, `camfree.c`, `CurveList.c`, `polynomial.c`, `ds.c`, `list.c`, `linklist.c`, `node.c`, `splytree.c`, `bintree.c`, `fileio.c`, `llfileio.c`, `fs_cli.c`, `filemc.c`, `Font.c`, `llglib.c`, `rand.c`, `orient.c`, `matrix.c`, `llmatrix.c`, `cu_801C1D84`, `cu_801CBC50` | 1/7/5/4/0 | 40 KiB | no |
| 0x801D134C-0x801DD498 | Memory manager, operator new and delete, memory card; movie playback (RCMP container, MAD video decoder) | `Memory.c`, `llmemory.c`, `MemExtern.c`, `TibNew.cpp`, `memorycard.c`, `moviercmp.cpp`, `maddec.cpp` | 0/2/2/5/1 | 44 KiB | no |
| 0x801DD498-0x801E11D0 | Particle systems | `particleLib.c`, `psysEmitter.c`, `psysCollision.c`, `colorRamp.c` | 0/1/1/1/0 | 12 KiB | no |
| 0x801E11D0-0x801EB488 | Controllers and input, collision shapes, rigid-body motion | `periph.c`, `llperiph.c`, `PJoyDrvr.c`, `cu_801E7034`, `cu_801E9BB4` | 0/0/1/0/2 | 36 KiB | no |
| 0x801EB488-0x801F3524 | Quaternions, button remapping, the resource system | `llquat.c`, `remap.c`, `Resource.c`, `reswrite.c`, `ResTracker.c`, `resquickload.c`, `rescache.c`, `resloosefile.c` | 0/0/2/2/0 | 25 KiB | no |
| 0x801F3524-0x801F8878 | Sound, speech and streaming; sorting; system start-up and timers | `sound.cpp`, `Speech.cpp`, `stream.c`, `sort.c`, `system.c`, `llsystem.c` | 0/1/1/3/0 | 19 KiB | no |
| 0x801F8878-0x8020DB34 | T3DB, the in-game database that every roster, stats and save query runs on | `t3db.c`, `t3db_io.c`, `T3DB_Compiler.c`, `T3DB_Lexer.c`, `t3db_query.c`, `t3db_table.c`, `tdbiores.c` ... | 0/0/4/3/1 | 68 KiB | no |
| 0x8020DB34-0x802176E8 | TM renderer: textures, models, materials, shaders, skeletons, blending | `texture.c`, `tmmodel.c`, `tmrender.c`, `tmclip.c`, `tmblend.c` ... | 1/1/1/1/0 | 10 KiB | no |
| 0x802176E8-0x8023873C | UIStudio menu engine, then engine code not yet identified (a viewport and name-registry group near 0x80227F14) | `src/Common/UIStudio/UIStudio.c`, `UISEvent.c`, `cu_8021A438`, `cu_80229270`, `cu_8022F428`, `cu_802355E4` | 1/1/0/1/5 | 126 KiB | no |

## Nintendo SDK and runtimes (`src/dolphin/`, `src/engine/`)

| Range | What it does in the game | Known files | Rungs 0/1/2/3/4 | Unlinked | Held |
| --- | --- | --- | --- | --- | --- |
| 0x80003100-0x800034A0 | Boot: `.init` code, including the `.init` part of `__ppc_eabi_init.c` (0x80003468-0x8000348C); that file's `.text` (0x8023E818-0x8023E920) is counted in the SDK row | `cu_80003100` | 1/0/0/1/0 | 1 KiB | no |
| 0x8023873C-0x8025E148 | GameCube SDK built with CodeWarrior: OS, DVD, VI, VM, PAD, AR, AI, MTX, GX, CARD, EXI, SI | `src/dolphin/<library>/*.c` | 6/8/1/5/1 | 42 KiB | no |
| 0x8025E148-0x80270B10 | C runtime: compiler support routines, C library, standard I/O and strings | `cu_8025E148` ... `cu_8026A664` | 0/0/1/3/3 | 74 KiB | no |
| 0x80270B10-0x8027EFAC | C++ decoder classes with a 3,432-byte state; what they decode is not read yet | `cu_802714A8`, `cu_80276DE4`, `cu_8027CF9C`, `cu_8027D3AC` | 0/0/2/0/3 | 57 KiB | no |
| 0x8027EFAC-0x80285A90 | Decompression: the `LZM1` descriptor and table-driven decoders | `cu_8027EFAC`, `lzm.c`, `cu_802821E8`, `cu_802832CC` | 0/0/0/3/0 | 21 KiB | no |
| 0x80285A90-end | SDK audio and extras: font, DSP, AX, GBA | `OSFont.c`, `dsp*.c`, `AX*.c`, `GBA*.c` | 1/1/0/0/0 | 2 KiB | no |

The site also lists 136,828 bytes (134 KiB) of code that no chunk owns yet (`Unmapped / Code section 2`, 62 non-exact functions); the structure pass assigns it to files.

## Work that is not on the ladder

- **Naming linked code.** Of the 480 linked files on 38935dd, 103 meet the closed-file rule; 307 still have `cu_` names and 374 hold 3,751 `fn_` functions. Closing them takes names, a header comment and evidence rows, not matching, which makes it good first work once file work resumes: claim one linked file, read it, name it.
- **Structure pass.** A boundary script built to the method in the project wiki's Tools chapter, section "Recover unit splits from a sibling build" (<https://mitsevox.github.io/wiki/tools/>), will propose file lists for the rung-4 chunks and the unmapped code, using NASCAR 2005's compile-unit list and the PS2 build's function order. Until it lands, rung-4 chunks take no function work.

## Keeping this page true

Update a row in the PR that changes it: a new file name, a link that moves a file off the ladder or a corrected description. Do not record single-file claims here; the open PRs are the record. Re-measure the rung counts from the site's `map.json` when a structure PR moves boundaries, and change the snapshot revision at the top.
