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
	
	
	public partial class CloudConfiguration : Smith.IXExtension.CloudConfigurationCF.CloudConfiguration, Neo.ApplicationFramework.Interfaces.ISupportMultiLanguage
	{
		
		public CloudConfiguration()
		{
			this.InitializeComponent();
			this.ApplyLanguageInternal();
		}
		
		private void InitializeComponent()
		{
			// 
			// CloudConfiguration
			// 
			this.Name = "CloudConfiguration";
			this.NamespaceId = new System.Guid("00000000-0000-0000-0000-000000000000");
			this.Uris = new System.Uri[] {
					new System.Uri("https://configuration.service.acirroplus.com", System.UriKind.Absolute)};
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
			Neo.ApplicationFramework.Tools.MultiLanguage.MultiLanguageResourceManager resources = new Neo.ApplicationFramework.Tools.MultiLanguage.MultiLanguageResourceManager(typeof(CloudConfiguration));
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
