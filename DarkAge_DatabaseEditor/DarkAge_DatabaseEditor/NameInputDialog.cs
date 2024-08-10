using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Xml;
using System.Xml.Linq;

namespace DarkAge_DatabaseEditor
{
	public partial class NameInputDialog : Form
	{
		private XElement targetXML;
		private string text;
		public string ResultText
		{
			get
			{
				return text;
			}
		}


		public NameInputDialog(XElement element)
		{
			InitializeComponent();
			targetXML = element;
		}

		private void NameInputDialogCancel_Click(object sender, EventArgs e)
		{
			this.Close();
		}

		private void NameInputDialogOK_Click(object sender, EventArgs e)
		{
			try
			{
				if (targetXML.Elements(NameInputDialogTextBox.Text).Any())
				{
					MessageBox.Show("이미 있는 이름", "Error");
				}
				else
				{
					text = XmlConvert.VerifyName(NameInputDialogTextBox.Text);
					this.DialogResult = DialogResult.OK;
					this.Close();
				}
			}
			catch (XmlException error)
			{
				MessageBox.Show(error.Message, "Error");
				return;
			}
		}
	}
}
