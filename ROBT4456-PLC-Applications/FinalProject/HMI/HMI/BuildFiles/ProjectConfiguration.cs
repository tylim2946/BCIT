//------------------------------------------------------------------------------
// <auto-generated>
//     This code was generated by a tool.
//     Runtime Version:4.0.30319.42000
//
//     Changes to this file may cause incorrect behavior and will be lost if
//     the code is regenerated.
// </auto-generated>
//------------------------------------------------------------------------------

namespace Neo.ApplicationFramework.Generated
{
	using Neo.ApplicationFramework.Tools.Actions;
	
	
	public partial class ProjectConfiguration : Neo.ApplicationFramework.Tools.ProjectConfiguration.ProjectConfiguration, Neo.ApplicationFramework.Interfaces.ISupportMultiLanguage
	{
		
		public ProjectConfiguration()
		{
			this.InitializeComponent();
			this.ApplyLanguageInternal();
		}
		
		private void InitializeComponent()
		{
			Neo.ApplicationFramework.Tools.ProjectConfiguration.FontSettings FontSettings1 = new Neo.ApplicationFramework.Tools.ProjectConfiguration.FontSettings();
			Neo.ApplicationFramework.Tools.ProjectConfiguration.FontSettings FontSettings2 = new Neo.ApplicationFramework.Tools.ProjectConfiguration.FontSettings();
			// 
			// ProjectConfiguration
			// 
			this.UISettings.Background = new Neo.ApplicationFramework.Common.Graphics.Logic.BrushCF(System.Drawing.Color.FromArgb(((int)(((byte)(167)))), ((int)(((byte)(188)))), ((int)(((byte)(214))))), System.Drawing.Color.Empty, Neo.ApplicationFramework.Interfaces.FillDirection.None);
			this.UISettings.ControlBackground = new Neo.ApplicationFramework.Common.Graphics.Logic.BrushCF(System.Drawing.Color.FromArgb(((int)(((byte)(115)))), ((int)(((byte)(148)))), ((int)(((byte)(190))))), System.Drawing.Color.Empty, Neo.ApplicationFramework.Interfaces.FillDirection.None);
			this.UISettings.ControlForeground = System.Drawing.Color.FromArgb(((int)(((byte)(255)))), ((int)(((byte)(255)))), ((int)(((byte)(255)))));
			FontSettings1.FamilyName = "Segoe UI Semibold";
			this.UISettings.Font = FontSettings1;
			this.UISettings.Foreground = System.Drawing.Color.FromArgb(((int)(((byte)(255)))), ((int)(((byte)(255)))), ((int)(((byte)(255)))));
			this.UISettings.ListItemHeight = 35;
			this.UISettings.MessageBoxDelay = System.TimeSpan.Parse("00:00:20");
			FontSettings2.FamilyName = "Segoe UI Black";
			FontSettings2.SizePixels = 22;
			this.UISettings.TitleFont = FontSettings2;
			this.ConnectDataBindings();
		}
		
		protected override void Dispose(bool disposing)
		{
			base.Dispose(disposing);
		}
		
		[System.ComponentModel.EditorBrowsableAttribute(System.ComponentModel.EditorBrowsableState.Never)]
		public virtual void ConnectDataBindings()
		{
		}
		
		private void InitializeObjectCreations()
		{
		}
		
		private void InitializeBeginInits()
		{
		}
		
		private void InitializeEndInits()
		{
		}
		
		[System.ComponentModel.EditorBrowsableAttribute(System.ComponentModel.EditorBrowsableState.Never)]
		private void ApplyLanguageInternal()
		{
			Neo.ApplicationFramework.Tools.MultiLanguage.MultiLanguageResourceManager resources = new Neo.ApplicationFramework.Tools.MultiLanguage.MultiLanguageResourceManager(typeof(ProjectConfiguration));
		}
		
		[System.ComponentModel.EditorBrowsableAttribute(System.ComponentModel.EditorBrowsableState.Never)]
		void Neo.ApplicationFramework.Interfaces.ISupportMultiLanguage.ApplyLanguage()
		{
			this.ApplyLanguage();
		}
		
		[System.ComponentModel.EditorBrowsableAttribute(System.ComponentModel.EditorBrowsableState.Never)]
		protected virtual void ApplyLanguage()
		{
			this.ApplyLanguageInternal();
		}
	}
}
