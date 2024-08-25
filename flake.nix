{
  description = "My talks";

  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs?ref=nixos-unstable";
    flake-utils.url = "github:numtide/flake-utils";
  };

  outputs = { self, nixpkgs, flake-utils }: 
    flake-utils.lib.eachDefaultSystem (system:
    let pkgs = import nixpkgs { system = "${system}"; config.allowUnfree = true; };
    in
      {
          devShells.default = pkgs.mkShell {
            buildInputs = [ pkgs.git pkgs.cmake pkgs.ninja pkgs.clang_16 pkgs.jetbrains.clion ];
          };
      }
    );
}
