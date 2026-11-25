#!/usr/bin/env bash
# Builds ArcweaveForUnreal.zip from the plugin files committed at a git ref.
# The zip holds a single Arcweave folder; copying it into a project's Plugins folder
# installs the plugin as Plugins/Arcweave.
#
# Usage: build-release-package.sh [ref] [output directory]
#
# The README and the marketing website link to this file name through
# https://github.com/arcweave/arcweave-unreal-plugin/releases/latest/download/ArcweaveForUnreal.zip,
# so renaming it breaks those links.
set -euo pipefail

ref="${1:-HEAD}"
mkdir -p "${2:-dist}"
out_dir=$(cd "${2:-dist}" && pwd)
zip="$out_dir/ArcweaveForUnreal.zip"
folder=Arcweave

# Only what Unreal needs to build and load the plugin, plus the license notices.
# Repository docs and contributor files stay out of the package.
paths=(arcweave.uplugin Config Resources Source LICENSE THIRD_PARTY_NOTICES.md)

for path in "${paths[@]}"; do
  git cat-file -e "$ref:$path" 2>/dev/null || { echo "$path does not exist at $ref" >&2; exit 1; }
done

# Only committed files are packaged, so local builds (Binaries, Intermediate) and untracked
# files never end up in a release.
rm -f "$zip"
git archive --format=zip --prefix="$folder/" -o "$zip" "$ref" -- "${paths[@]}"

entries=$(git archive --prefix="$folder/" "$ref" -- "${paths[@]}" | tar -t)
grep -qx "$folder/arcweave.uplugin" <<< "$entries" ||
  { echo "The package has no $folder/arcweave.uplugin" >&2; exit 1; }
built=$(grep -E "^$folder/(Binaries|Intermediate)/" <<< "$entries" || true)
[ -z "$built" ] || { printf 'The package contains build output:\n%s\n' "$built" >&2; exit 1; }

echo "Built $zip from $ref"
