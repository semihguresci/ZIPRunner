// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;


namespace Workarounds
{
    using System;
    using System.IO;

    public class BuildVersionWorkaround
    {
        // For testing only
        private static void Main()
        {
            var currentDir = Environment.CurrentDirectory;
            SearchFiles(currentDir);
        }

        public static void ExecuteWorkaround(string path)
        {
            var rootDirectory = Path.GetDirectoryName(path);

            Console.WriteLine($"Module path => {rootDirectory}");

            var targetFixDirectory = Path.Combine(rootDirectory, "Intermediate", "Build");

            Console.WriteLine($"Fix target path => {targetFixDirectory}");

            SearchFiles(targetFixDirectory);

            // Credits to mukund-dh => https://github.com/EpicGames/UnrealEngine/pull/9067#issuecomment-1114244797
            var pluginFixDirectory = Path.Combine(rootDirectory, "Plugins");

            DirectoryInfo pluginInfo = new DirectoryInfo(pluginFixDirectory);
            if (pluginInfo.Exists)
            {
                DirectoryInfo[] plugs = pluginInfo.GetDirectories();

                foreach (DirectoryInfo pl in plugs)
                {
                    var plgDir = Path.Combine(pluginFixDirectory, pl.Name, "Intermediate", "Build");
                    Console.WriteLine($"Fix plugin path => {plgDir}");
                    SearchFiles(plgDir);
                }
            }

            Console.WriteLine($"Everything Done");
        }

        const string FilterName = "*.json";
        private static void SearchFiles(string path)
        {
            var info = new DirectoryInfo(path);

            var files = info.GetFiles(FilterName);

            foreach (var file in files)
            {
                using var filestream = file.Open(FileMode.Open, FileAccess.ReadWrite, FileShare.None);
                FixFile(filestream);
            }

            var directories = info.GetDirectories();

            foreach (var directory in directories)
            {
                SearchFiles(directory.FullName);
            }
        }

        const string OriginPattern = "\"Version\": \"1.2\",";
        const string TargetPattern = "\"Version\": \"1.1\",";
        private static void FixFile(FileStream FileStream)
        {
            using var reader = new StreamReader(FileStream);

            // Not the optimal way but probably good enough.
            var text = reader.ReadToEnd();
            if (text.Contains(OriginPattern))
            {
                Console.WriteLine($"Fixing => {FileStream.Name}");
                text = text.Replace(OriginPattern, TargetPattern);

                // Restart file position
                FileStream.Position = 0;

                using var writer = new StreamWriter(FileStream);
                writer.Write(text);
                writer.Flush();

                // Arrays start at 0 but sizes doesn't
                var newSize = FileStream.Position + 1;

                if (newSize != FileStream.Length)
                {
                    FileStream.SetLength(newSize);
                }

                FileStream.Flush();
            }
        }
    }
}


public class ZipZipBall : ModuleRules
 {
	public ZipZipBall(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
        Workarounds.BuildVersionWorkaround.ExecuteWorkaround(Target.ProjectFile.ToNormalizedPath());
        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "HTTP", "Json", "JsonUtilities", "Sockets", "Networking", "GameplayTags", "AppLovinMAX" });
	}
}
