class CfgPatches
{
	class SchanaModTraderNametags
	{
		requiredAddons[] =
		{
			"DZ_Data",
			"Trader"
		};
	};
};

class CfgMods
{
	class SchanaModTraderNametags
	{
		name = "SchanaModTraderNametags";
		action = "https://github.com/schana/dayz-mod-trader-nametags";
		author = "schana";
		type = "mod";

		class defs
		{
			class missionScriptModule
			{
				value = "";
				files[] = {
					"SchanaModTraderNametags/Mission"
				};
			};
		};
	};
};
