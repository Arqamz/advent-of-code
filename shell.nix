{ pkgs ? import <nixpkgs> {} }:

let
  # Haskell environment setup
  haskellEnv = pkgs.ghc;

  # Elixir environment setup
  elixirEnv = pkgs.elixir_1_15;

  # Python environment setup
  pythonEnv = pkgs.python312Full;

  # C++ / C development tools setup
  cppEnv = pkgs.libgcc;
  cppTools = pkgs.gnumake;
  clangEnv = pkgs.libclang;

in pkgs.mkShell rec {
  name = "advent-of-code-env";

  packages = [
    haskellEnv
    elixirEnv
    pythonEnv
    cppEnv
    cppTools
    clangEnv
  ];

  shellHook = ''
    echo "Welcome to the Advent of Code environment!"
    echo "Available languages: Elixir, Haskell, Python, C++, C"
    echo "Use 'ghc', 'elixir', 'python3', 'gcc', or 'clang' to start coding!"
  '';

#   # Add useful environment variables (optional)
#   shellInit = ''
#     export LANG="en_US.UTF-8"
#     export PATH="$PATH:${elixirEnv}/bin:${haskellEnv}/bin:${pythonEnv}/bin:${cppEnv}/bin"
#   '';
}
