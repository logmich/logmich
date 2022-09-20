{
  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-22.05";
    flake-utils.url = "github:numtide/flake-utils";

    tinycmmc.url = "gitlab:grumbel/tinycmmc";
    tinycmmc.inputs.nixpkgs.follows = "nixpkgs";
    tinycmmc.inputs.flake-utils.follows = "flake-utils";
  };

  outputs = { self, nixpkgs, flake-utils, tinycmmc }:
    flake-utils.lib.eachDefaultSystem (system:
      let
        pkgs = nixpkgs.legacyPackages.${system};
      in {
        packages = rec {
          default = logmich;

          logmich = pkgs.stdenv.mkDerivation {
            pname = "logmich";
            version = "0.1.x-" + (if (self ? shortRev) then self.shortRev else "dirty");

            src = nixpkgs.lib.cleanSource ./.;

            nativeBuildInputs = [
              pkgs.cmake
            ];

            buildInputs = [
              tinycmmc.packages.${system}.default
            ];

            propagatedBuildInputs = [
              pkgs.boost
            ];
           };
        };
      }
    );
}
