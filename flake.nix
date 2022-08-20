{
  description = "Software Surface Library";

  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-22.05";

    tinycmmc.url = "github:grumbel/tinycmmc";
    tinycmmc.inputs.nixpkgs.follows = "nixpkgs";
    tinycmmc.inputs.flake-utils.follows = "flake-utils";
  };

  outputs = { self, nixpkgs, tinycmmc }:
    tinycmmc.lib.eachSystemWithPkgs (pkgs:
      {
        packages = rec {
          default = logmich;
          logmich = pkgs.callPackage ./logmich.nix {
            tinycmmc = tinycmmc.packages.${pkgs.system}.default;
          };
        };
      }
    );
}
