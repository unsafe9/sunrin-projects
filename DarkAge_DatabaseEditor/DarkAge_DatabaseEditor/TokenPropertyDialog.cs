using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace DarkAge_DatabaseEditor
{
	public partial class TokenPropertyDialog : Form
	{
		public enum Type
		{
			Buff,
			Debuff
		}

		private TokenPropertyItem item;
		public TokenPropertyItem ResultItem
		{
			get
			{
				return item;
			}
		}

		public TokenPropertyDialog(Type type, ListBox list)
		{
			InitializeComponent();

			string[] temp = new string[list.Items.Count];
			for (int i = 0; i < temp.Length; ++i)
			{
				temp[i] = list.Items[i].ToString();
			}

			if (type == Type.Buff)
			{
				for (int i = 0; i < MainFrame.TokenBuffItems.Length; ++i)
				{
					if (!temp.Contains(MainFrame.TokenBuffItems[i]))
					{
						ComboBox.Items.Add(MainFrame.TokenBuffItems[i]);
					}
				}
			}
			else
			{
				for (int i = 0; i < MainFrame.TokenDebuffItems.Length; ++i)
				{
					if (!temp.Contains(MainFrame.TokenDebuffItems[i]))
					{
						ComboBox.Items.Add(MainFrame.TokenDebuffItems[i]);
					}
				}
			}
			if (ComboBox.Items.Count == 0)
			{
				MessageBox.Show("추가 할 요소가 없습니다.");
				this.DialogResult = DialogResult.Cancel;
				this.Close();
			}
			ComboBox.SelectedIndex = 0;
			TargetComboBox.SelectedIndex = 0;
		}
		public TokenPropertyDialog(Type type, TokenPropertyItem item)
		{
			InitializeComponent();

			ComboBox.Items.Add(item.text);
			ComboBox.SelectedIndex = 0;
			ComboBox.Enabled = false;

			Num1.Value = item.num1;
			Num2.Value = item.num2;
			TargetComboBox.SelectedIndex = (int)item.target;
			TurnNum.Value = item.turn;
		}

		private void Cancel_Click(object sender, EventArgs e)
		{
			this.Close();
		}

		private void OK_Click(object sender, EventArgs e)
		{
			item = new TokenPropertyItem();
			item.text = ComboBox.GetItemText(ComboBox.SelectedItem);
			item.num1 = (short)Num1.Value;
			item.num2 = (short)Num2.Value;
			item.target = (TokenTarget)TargetComboBox.SelectedIndex;
			item.turn = (ushort)TurnNum.Value;

			this.DialogResult = DialogResult.OK;
			this.Close();
		}
	}
}
