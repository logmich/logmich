{
  description = "Software Surface Library";

  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-22.05";
    flake-utils.url = "github:numtide/flake-utils";

    tinycmmc.url = "github:grumbel/tinycmmc";
    tinycmmc.inputs.nixpkgs.follows = "nixpkgs";
    tinycmmc.inputs.flake-utils.follows = "flake-utils";
  };

  outputs = { self, nixpkgs, flake-utils, tinycmmc }:
    flake-utils.lib.eachDefaultSystem (system:
      let
        pkgs = nixpkgs.legacyPackages.${system};
      in rec {
        packages = flake-utils.lib.flattenTree {
          logmich = pkgs.stdenv.mkDerivation {
            pname = "logmich";
            version = "0.2.0";
            src = nixpkgs.lib.cleanSource ./.;
            nativeBuildInputs = [
              pkgs.cmake
            ];
            buildInputs = [
              tinycmmc.defaultPackage.${system}
            ];
            propagatedBuildInputs = [
              pkgs.fmt
            ];
           };
        };
        defaultPackage = packages.logmich;
      });
}
