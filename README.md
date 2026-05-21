# Requiem of Remembrance
Hack and slash/Sekiro style combat linear story game with a narrative and immersive focus

## Git Flow

## 1. Branch Architecture

The following diagram illustrates the full lifecycle of a change — from idea to production:

```
main ──────────────────────────────────────────────────────────► (stable releases)
  │                                                    ▲
  │  hotfix/v1.2.1 ────────────────────────────────►──┤
  │                                                    │
develop ───────────────────────────────────────────────┤──────► (integration hub)
  │          ▲             ▲              ▲             │
  │          │             │              │             │
feature/  bugfix/      feature/     experimental/      │
player-   BUG-042      ui-hud       physics-v2         │
movement                                               │
  └──────────┴─────────────┴──────────────────────────►┘
```

---

### `main` — Production Branch

The **single source of truth** for shipped code. Every commit on this branch represents a version that has been tested.

**Rules:**

- Direct commits are **strictly forbidden**.
- Merges into `main` come **only** from `hotfix/*` or `develop` (via a Release PR).
- Every merge must be **tagged** with a semantic version.

```bash
# Tagging a release on main
git tag -a v1.2.0 -m "Release v1.2.0 — Combat system overhaul"
git push origin v1.2.0
```

---

### `develop` — Integration Hub

The **central integration branch**. All completed and reviewed features, bugfixes, and assets are merged here before they move into QA. Consider `develop` permanently "unstable but functional" — it should always build, but is not guaranteed to be release-ready.

**Rules:**

- Direct commits are **strictly forbidden**.
- Must pass CI automated build checks on every merge.
- QA team runs nightly builds from this branch.

---

### `feature/[feature-name]` — Feature Branches

Used for implementing any new mechanic, system, tool, UI screen, or asset pipeline. Branch lifespan should be **short** (ideally under 2 weeks). Long-lived feature branches accumulate more conflictt with previous versions.

**Naming convention:**

```
feature/[system]-[descriptor]

Examples:
  feature/player-movement
  feature/inventory-drag-drop
  feature/audio-adaptive-music
  feature/vfx-muzzle-flash
  feature/ui-main-menu
  feature/ai-patrol-behavior
```

**Lifecycle:**

```bash
# 1. Always branch off develop
git checkout develop
git pull origin develop
git checkout -b feature/player-movement

# 2. Work, commit frequently with meaningful messages
git add .
git commit -m "feat(player): add coyote time to jump system"

# 3. Keep your branch updated with develop to reduce merge debt
git fetch origin
git rebase origin/develop

# 4. Open a Pull Request → develop when done
```

---

### `bugfix/[ticket-id]` — Bug Fix Branches

Used to address bugs found during QA cycles or integration testing on `develop`. Always references a **ticket ID** from your project management tool (Jira, Linear, GitHub Issues, etc.).

**Naming convention:**

```
bugfix/[tracker-prefix]-[id]-[short-description]

Examples:
  bugfix/GAME-042-player-clips-through-floor
  bugfix/GAME-107-audio-loop-not-stopping
  bugfix/GAME-218-ui-score-overflow
```

**Lifecycle:**

```bash
# Branch off develop
git checkout develop
git pull origin develop
git checkout -b bugfix/GAME-042-player-clips-through-floor

# Fix, commit, PR back into develop
git commit -m "fix(physics): adjust capsule collider radius to prevent floor clipping [GAME-042]"
```

---

### `hotfix/[v.num]` — Critical Hotfix Branches

Reserved for **critical production bugs** that cannot wait for the next regular release cycle — crashes, data loss, game-breaking exploits, or cert failures on console platforms.

**Naming convention:**

```
hotfix/v[MAJOR].[MINOR].[PATCH]

Examples:
  hotfix/v1.2.1
  hotfix/v2.0.1
```

**Lifecycle (the only branch that merges into BOTH `main` AND `develop`):**

```bash
# 1. Branch off main (NOT develop)
git checkout main
git pull origin main
git checkout -b hotfix/v1.2.1

# 2. Apply the fix
git commit -m "fix(crash): resolve null reference on save file load [CRITICAL]"

# 3. PR → main (get emergency approval from Lead + QA)
# 4. Tag the new patch on main
git tag -a v1.2.1 -m "Hotfix v1.2.1 — Critical save file crash"

# 5. ALSO merge back into develop to keep it in sync
git checkout develop
git merge hotfix/v1.2.1
git push origin develop
```

> ⚠️ **Critical:** Forgetting to back-merge a hotfix into `develop` is one of the most common mistakes in production teams. Make it a required checklist item in your hotfix PR template.

---

### `experimental/[idea]` — Experimental / Prototype Branches

Safe sandbox for risky ideas, technology spikes, or proof-of-concept work. These branches have **no guaranteed merge path** into `develop`. They may be abandoned, archived, or cherry-picked from.

**Naming convention:**

```
experimental/[concept-or-tech]

Examples:
  experimental/physics-destructions-v2
  experimental/procedural-level-gen
  experimental/nanite-foliage-test
  experimental/ml-agents-enemy-ai
```

**Lifecycle:**

```bash
git checkout develop
git checkout -b experimental/procedural-level-gen

# Work freely — no strict PR process required
# If the experiment succeeds and is approved for integration,
# cherry-pick relevant commits or create a proper feature branch
git cherry-pick <commit-hash>
```

---

## 2. Work Protocol

### 2.1 Naming Conventions — Summary

| Branch Type  | Pattern                                  | Example                                |
| ------------ | ---------------------------------------- | -------------------------------------- |
| Production   | `main`                                   | `main`                                 |
| Integration  | `develop`                                | `develop`                              |
| Feature      | `feature/[system]-[descriptor]`          | `feature/player-double-jump`           |
| Bug Fix      | `bugfix/[TICKET-ID]-[short-description]` | `bugfix/GAME-305-camera-gimbal-lock`   |
| Hotfix       | `hotfix/v[X].[Y].[Z]`                    | `hotfix/v2.1.3`                        |
| Experimental | `experimental/[concept]`                 | `experimental/voxel-terrain-streaming` |

**Commit message convention** (follow [Conventional Commits](https://www.conventionalcommits.org/)):

```
<type>(<scope>): <short description> [TICKET-ID]

Types: feat | fix | refactor | perf | docs | chore | test | ci
Scope: player | enemy | ui | audio | vfx | physics | camera | build | tools

Examples:
  feat(player): implement wall-run mechanic [GAME-88]
  fix(audio): prevent BGM overlap on scene reload [GAME-102]
  perf(vfx): reduce particle draw calls by 40% on mobile [GAME-115]
  chore(build): update Unreal Engine version to 5.4
```

---
