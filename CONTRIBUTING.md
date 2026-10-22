# Contributing to Paper Mario DX

If you want to talk an idea through before you start, ask on the [Star Haven Discord server](https://discord.gg/pwhSQbH) in [#papermario-dx](https://discord.com/channels/279322074412089344/1099844075399696394).

## Building

Follow the [building guide](https://docs.starhaven.dev/papermario-dx/testing/building/), or from a terminal run:

```sh
nix develop -c ninja
```

Test your change in the game before you open a pull request. The [debug menu](https://docs.starhaven.dev/papermario-dx/testing/debug-menu/) can get you to most maps and battles quickly.

## Code style

Write the clearest modern C you can, and use C++ where it makes something much simpler. Run `treefmt` inside `nix develop` to format your changes before you push. Pull requests with unformatted files don't pass their checks.

## Commits

Write commit summaries in lowercase, saying what the commit does, such as `merge include/ into src/`. If the reason for the change isn't obvious from the diff, explain it in the body.

## Pull requests

Open pull requests against `main` on [Tangled](https://tangled.org/starhaven.dev/papermario-dx/pulls/new). Keep each one to a single change, so it's easy to review and to describe in the changelog.

If your changes build on each other, you can submit them as a stack of pull requests that are reviewed one at a time. Stacks need [Jujutsu](https://jj-vcs.github.io/jj/), and [Jujutsu on Tangled](https://blog.tangled.org/stacking/) explains how to submit one.

## Changelog

Modders find out what changed from the changelog in `manual/changelog.md`. Each release's notes also become the release's tag message, and they appear on the [changelog page](https://docs.starhaven.dev/papermario-dx/changelog/) in the manual.

### In a pull request

If modders will notice your change, add a bullet to the Unreleased section of the changelog. Say what changed and, if they have to do something after updating, what to do. If it isn't obvious who will notice and why, add a sentence about that too. It's much easier to write now than to dig out of the diff later.

Leave out changes outside `src` and `assets`, such as to `tools`, CI, or the release scripts, unless modders will notice them another way, such as a slower build. Diorama64 shows only the files in the asset stack by default, so most modders never see the rest.

### Before a release

Just before running `tools/release.py`, rewrite the Unreleased bullets into release notes. The [Rust release announcements](https://blog.rust-lang.org/releases/) are a good model: each one picks a few changes worth reading about, explains each in a few short paragraphs, and lists the rest.

Start by gathering everything since the last release: the Unreleased bullets, `jj log -r 'dx-YYYY-MM-DD..main'`, and the pull request descriptions. Some changes that modders will notice won't have a bullet, so look through the commits as well. Then decide what to leave out. A debugging convenience or a tidier asset dump isn't worth a reader's time, even if it took a while to make.

Give each change worth explaining its own `###` section. `release.py` puts the notes under a `## YYYY-MM-DD` heading, so `##` is taken. Order the sections like this:

1. Changes that break existing mods. Close each one with what to do.
2. New features, the most interesting first.
3. Fixes that unblock a whole platform or workflow, such as an editor that didn't open on Linux.
4. Build and tooling changes.
5. An **Other changes** list, with a line for each smaller change. A breaking change that only affects unusual setups can go here too.

If one section relies on another, put the one it relies on first, so that neither has to say "see below".

The heading names the change, such as "Music browser in the debug menu", not what it's good for. A fix says so: "Star Rod fixed on Linux". End the heading with a credit to whoever wrote the commits, linked to their page on starhaven.dev:

```markdown
### Music browser in the debug menu ([Brando](https://starhaven.dev/brando.tngl.sh))
```

Use the display name from their starhaven.dev profile. If they haven't set one, use the name on their commits. In **Other changes**, put the credit at the end of the line.

Open each section with what changed, using "now", "no longer", or a verb like "adds". After that, describe how things work in the present tense. Only mention how things used to work if the change doesn't make sense without it, and then use the past tense ("Previously, …").

Write about the change, not the reader. "Mod code is compiled the same way" reads better than "Your mod's code is compiled the same way". For instructions, use the imperative: "Move any headers in `include/` into `src/`." Don't refer to Paper Mario DX by name; it's clear what the notes are about.

Keep it short. Cut anything a modder would assume anyway, and anything they won't act on, such as where a tool runs or an edge case they're unlikely to hit. Keep measurements approximate ("a few percent faster") and leave out how they were taken. Before you publish, check every number and name against the diff.

When you mention a function or macro that has a reference page, link to it. The address is the header's path under `src/` plus the symbol, such as [`https://docs.starhaven.dev/papermario-dx/reference/rumble/#reset_max_rumble_duration`](https://docs.starhaven.dev/papermario-dx/reference/rumble/#reset_max_rumble_duration) for `reset_max_rumble_duration` in `src/rumble.h`. Not every header has a page, so open the link to make sure it works. Link to a manual page when one covers the change. Add a screenshot to a section about something modders can see in the game.

Don't commit screenshots to the repository, since every clone would carry them forever. Upload them to your [PDS](https://atproto.com/guides/glossary#pds-personal-data-server) instead, with [goat](https://github.com/bluesky-social/goat):

```sh
goat account login -u your.handle -p your-app-password
goat blob upload screenshot.png > blob.json
```

A PDS deletes a blob that no record refers to, so create a record for it:

```sh
jq '{"$type": "dev.starhaven.image", image: ., alt: "What the screenshot shows"}' blob.json > record.json
goat record create --no-validate record.json
```

The image's address is `https://<your PDS>/xrpc/com.atproto.sync.getBlob?did=<your DID>&cid=<cid>`, where the CID is the `$link` in `blob.json`. `goat resolve your.handle` prints your DID and PDS.
