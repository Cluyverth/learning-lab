{
  description = "Inkryn - Development environment";

  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";
    flake-utils.url = "github:numtide/flake-utils";
  };

  outputs = { nixpkgs, flake-utils, ... }:
    flake-utils.lib.eachDefaultSystem (system:
      let
        pkgs = nixpkgs.legacyPackages.${system};
      in
      {
        devShells.default = pkgs.mkShell {
          buildInputs = with pkgs; [
            bashInteractive
            git
            nixpkgs-fmt
            bun
            typescript-language-server
            postgresql
            unzip
            p7zip
            biome
            python315
            # Add more packages as needed for your project
          ];

          env = {
            # Set any necessary environment variables here
          };

          shellHook = ''
            echo "Welcome to the Inkryn development shell!"
            echo "🚀 Starting enviroment..."
            echo "✅ Environment ready!"
          '';
        };
      }
    );
}
