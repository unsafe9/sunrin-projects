using System;
using System.Collections;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Xml.Linq;
using System.Xml;
using System.IO;

namespace DarkAge_DatabaseEditor
{
	public partial class MainFrame : Form
	{
		#region XML Properties
		private XElement PlayerXML;
		private XElement EnemyXML;
		private XElement TokenXML;
		private XElement ArmorXML;
		private XElement WeaponXML;
		private XElement PerkXML;
		private XElement ItemXML;
		#endregion

		public MainFrame()
		{
			InitializeComponent();

			MainTabControl.ItemSize = new Size(MainTabControl.Width / MainTabControl.TabCount - 1, MainTabControl.ItemSize.Height);

			#region Initialize Player Tab

			PlayerListLastIndex = -1;
			if (File.Exists("Players.xml"))
			{
				PlayerXML = XElement.Load("Players.xml");
				foreach (XElement x in PlayerXML.Elements())
				{
					PlayerList.Items.Add(x.Name);
				}
				if (PlayerList.Items.Count > 0)
				{
					PlayerList.SelectedIndex = 0;
				}
			}
			else
			{
				PlayerXML = new XElement(PlayerTab.Text);
				PlayerSaveXML();
			}

			#endregion Initialize Player Tab

			#region Initialize Enemy Tab

			EnemyListLastIndex = -1;
			if (File.Exists("Enemies.xml"))
			{
				EnemyXML = XElement.Load("Enemies.xml");
				foreach (XElement x in EnemyXML.Elements())
				{
					EnemyList.Items.Add(x.Name);
				}
				if (EnemyList.Items.Count > 0)
				{
					EnemyList.SelectedIndex = 0;
				}
			}
			else
			{
				EnemyXML = new XElement(EnemyTab.Text);
				EnemySaveXML();
			}

			#endregion Initialize Enemy Tab

			#region Initialize Token Tab

			TokenListLastIndex = -1;
			if (File.Exists("Tokens.xml"))
			{
				TokenXML = XElement.Load("Tokens.xml");
				foreach (XElement x in TokenXML.Elements())
				{
					TokenList.Items.Add(x.Name);
				}
				if (TokenList.Items.Count > 0)
				{
					TokenList.SelectedIndex = 0;
				}
			}
			else
			{
				TokenXML = new XElement(TokenTab.Text);
				TokenSaveXML();
			}

			#endregion Initialize Token Tab

			#region Initialize Armor Tab

			ArmorListLastIndex = -1;
			if (File.Exists("Armors.xml"))
			{
				ArmorXML = XElement.Load("Armors.xml");
				foreach (XElement x in ArmorXML.Elements())
				{
					ArmorList.Items.Add(x.Name);
				}
				if (ArmorList.Items.Count > 0)
				{
					ArmorList.SelectedIndex = 0;
				}
			}
			else
			{
				ArmorXML = new XElement(ArmorTab.Text);
				ArmorSaveXML();
			}

			#endregion Initialize Armor Tab

			#region Initialize Weapon Tab

			WeaponListLastIndex = -1;
			if (File.Exists("Weapons.xml"))
			{
				WeaponXML = XElement.Load("Weapons.xml");
				foreach (XElement x in WeaponXML.Elements())
				{
					WeaponList.Items.Add(x.Name);
				}
				if (WeaponList.Items.Count > 0)
				{
					WeaponList.SelectedIndex = 0;
				}
			}
			else
			{
				WeaponXML = new XElement(WeaponTab.Text);
				WeaponSaveXML();
			}

			#endregion Initialize Weapon Tab

			#region Initialize Perk Tab

			PerkListLastIndex = -1;
			if (File.Exists("Perks.xml"))
			{
				PerkXML = XElement.Load("Perks.xml");
				foreach (XElement x in PerkXML.Elements())
				{
					PerkList.Items.Add(x.Name);
				}
				if (PerkList.Items.Count > 0)
				{
					PerkList.SelectedIndex = 0;
				}
			}
			else
			{
				PerkXML = new XElement(PerkTab.Text);
				PerkSaveXML();
			}

			#endregion Initialize Perk Tab

			#region Initialize Item Tab

			ItemListLastIndex = -1;
			if (File.Exists("Items.xml"))
			{
				ItemXML = XElement.Load("Items.xml");
				foreach (XElement x in ItemXML.Elements())
				{
					ItemList.Items.Add(x.Name);
				}
				if (ItemList.Items.Count > 0)
				{
					ItemList.SelectedIndex = 0;
				}
			}
			else
			{
				ItemXML = new XElement(ItemTab.Text);
				ItemSaveXML();
			}

			#endregion Initialize Item Tab
		}

		#region Player Tab

		private int PlayerListLastIndex;
		private bool PlayerPreventDataSave = false;

		private void PlayerSaveXML()
		{
			PlayerXML.Save("Players.xml");
		}
		private void PlayerComponentClear()
		{
			PlayerNameTextBox.Text = "";
			PlayerLevelNum.Value = 1;

			PlayerHPInitNum.Value = 0;
			PlayerHPRateNum.Value = 0;
			PlayerHPNum.Value = 0;
			PlayerHP_ReInitNum.Value = 0;
			PlayerHP_ReRateNum.Value = 0;
			PlayerHP_ReNum.Value = 0;
			PlayerMPNum.Value = 0;
			PlayerMPRateNum.Value = 0;
			PlayerMPInitNum.Value = 0;
			PlayerMP_ReInitNum.Value = 0;
			PlayerMP_ReRateNum.Value = 0;
			PlayerMP_ReNum.Value = 0;
			PlayerSPInitNum.Value = 0;
			PlayerSPRateNum.Value = 0;
			PlayerSPNum.Value = 0;
			PlayerSP_ReInitNum.Value = 0;
			PlayerSP_ReRateNum.Value = 0;
			PlayerSP_ReNum.Value = 0;
			PlayerSpeedInitNum.Value = 0;
			PlayerSpeedRateNum.Value = 0;
			PlayerSpeedNum.Value = 0;
			PlayerDMGInitNum.Value = 0;
			PlayerDMGRateNum.Value = 0;
			PlayerDMGNum.Value = 0;
			PlayerDEFInitNum.Value = 0;
			PlayerDEFRateNum.Value = 0;
			PlayerDEFNum.Value = 0;
			PlayerEXPBaseInitNum.Value = 0;
			PlayerEXPBaseRateNum.Value = 0;
			PlayerEXPBaseNum.Value = 0;
			PlayerEXPGapInitNum.Value = 0;
			PlayerEXPGapRateNum.Value = 0;
			PlayerEXPGapNum.Value = 0;
			PlayerEXPNum.Value = 0;
		}
		private void PlayerComponentEnabled(bool b)
		{
			PlayerNameTextBox.Enabled = b;
			PlayerLevelNum.Enabled = b;
			PlayerHPNum.Enabled = b;
			PlayerHPInitNum.Enabled = b;
			PlayerHPRateNum.Enabled = b;
			PlayerHP_ReNum.Enabled = b;
			PlayerHP_ReInitNum.Enabled = b;
			PlayerHP_ReRateNum.Enabled = b;
			PlayerMPNum.Enabled = b;
			PlayerMPInitNum.Enabled = b;
			PlayerMPRateNum.Enabled = b;
			PlayerMP_ReNum.Enabled = b;
			PlayerMP_ReInitNum.Enabled = b;
			PlayerMP_ReRateNum.Enabled = b;
			PlayerSPNum.Enabled = b;
			PlayerSPInitNum.Enabled = b;
			PlayerSPRateNum.Enabled = b;
			PlayerSP_ReNum.Enabled = b;
			PlayerSP_ReInitNum.Enabled = b;
			PlayerSP_ReRateNum.Enabled = b;
			PlayerSpeedNum.Enabled = b;
			PlayerSpeedInitNum.Enabled = b;
			PlayerSpeedRateNum.Enabled = b;
			PlayerDMGNum.Enabled = b;
			PlayerDMGInitNum.Enabled = b;
			PlayerDMGRateNum.Enabled = b;
			PlayerDEFNum.Enabled = b;
			PlayerDEFInitNum.Enabled = b;
			PlayerDEFRateNum.Enabled = b;
			PlayerEXPBaseNum.Enabled = b;
			PlayerEXPBaseInitNum.Enabled = b;
			PlayerEXPBaseRateNum.Enabled = b;
			PlayerEXPGapNum.Enabled = b;
			PlayerEXPGapInitNum.Enabled = b;
			PlayerEXPGapRateNum.Enabled = b;
			PlayerEXPNum.Enabled = b;
		}
		private void PlayerLoadXMLToComponent(string player)
		{
			PlayerNameTextBox.Text = player;
			PlayerLevelNum.Value = 1;

			PlayerHPInitNum.Value = Decimal.Parse(PlayerXML.Element(player).Element(PlayerHPLabel.Text).Element("Init").Value);
			PlayerHPRateNum.Value = Decimal.Parse(PlayerXML.Element(player).Element(PlayerHPLabel.Text).Element("Rate").Value);
			PlayerHPNum.Value = PlayerHPInitNum.Value + (PlayerLevelNum.Value - 1) * PlayerHPRateNum.Value;
			PlayerHP_ReInitNum.Value = Decimal.Parse(PlayerXML.Element(player).Element(PlayerHP_ReLabel.Text).Element("Init").Value);
			PlayerHP_ReRateNum.Value = Decimal.Parse(PlayerXML.Element(player).Element(PlayerHP_ReLabel.Text).Element("Rate").Value);
			PlayerHP_ReNum.Value = PlayerHP_ReInitNum.Value + (PlayerLevelNum.Value - 1) * PlayerHP_ReRateNum.Value;
			PlayerMPInitNum.Value = Decimal.Parse(PlayerXML.Element(player).Element(PlayerMPLabel.Text).Element("Init").Value);
			PlayerMPRateNum.Value = Decimal.Parse(PlayerXML.Element(player).Element(PlayerMPLabel.Text).Element("Rate").Value);
			PlayerMPNum.Value = PlayerMPInitNum.Value + (PlayerLevelNum.Value - 1) * PlayerMPRateNum.Value;
			PlayerMP_ReInitNum.Value = Decimal.Parse(PlayerXML.Element(player).Element(PlayerMP_ReLabel.Text).Element("Init").Value);
			PlayerMP_ReRateNum.Value = Decimal.Parse(PlayerXML.Element(player).Element(PlayerMP_ReLabel.Text).Element("Rate").Value);
			PlayerMP_ReNum.Value = PlayerMP_ReInitNum.Value + (PlayerLevelNum.Value - 1) * PlayerMP_ReRateNum.Value;
			PlayerSPInitNum.Value = Decimal.Parse(PlayerXML.Element(player).Element(PlayerSPLabel.Text).Element("Init").Value);
			PlayerSPRateNum.Value = Decimal.Parse(PlayerXML.Element(player).Element(PlayerSPLabel.Text).Element("Rate").Value);
			PlayerSPNum.Value = PlayerSPInitNum.Value + (PlayerLevelNum.Value - 1) * PlayerSPRateNum.Value;
			PlayerSP_ReInitNum.Value = Decimal.Parse(PlayerXML.Element(player).Element(PlayerSP_ReLabel.Text).Element("Init").Value);
			PlayerSP_ReRateNum.Value = Decimal.Parse(PlayerXML.Element(player).Element(PlayerSP_ReLabel.Text).Element("Rate").Value);
			PlayerSP_ReNum.Value = PlayerSP_ReInitNum.Value + (PlayerLevelNum.Value - 1) * PlayerSP_ReRateNum.Value;
			PlayerSpeedInitNum.Value = Decimal.Parse(PlayerXML.Element(player).Element(PlayerSpeedLabel.Text).Element("Init").Value);
			PlayerSpeedRateNum.Value = Decimal.Parse(PlayerXML.Element(player).Element(PlayerSpeedLabel.Text).Element("Rate").Value);
			PlayerSpeedNum.Value = PlayerSpeedInitNum.Value + (PlayerLevelNum.Value - 1) * PlayerSpeedRateNum.Value;
			PlayerDMGInitNum.Value = Decimal.Parse(PlayerXML.Element(player).Element(PlayerDMGLabel.Text).Element("Init").Value);
			PlayerDMGRateNum.Value = Decimal.Parse(PlayerXML.Element(player).Element(PlayerDMGLabel.Text).Element("Rate").Value);
			PlayerDMGNum.Value = PlayerDMGInitNum.Value + (PlayerLevelNum.Value - 1) * PlayerDMGRateNum.Value;
			PlayerDEFInitNum.Value = Decimal.Parse(PlayerXML.Element(player).Element(PlayerDEFLabel.Text).Element("Init").Value);
			PlayerDEFRateNum.Value = Decimal.Parse(PlayerXML.Element(player).Element(PlayerDEFLabel.Text).Element("Rate").Value);
			PlayerDEFNum.Value = PlayerDEFInitNum.Value + (PlayerLevelNum.Value - 1) * PlayerDEFRateNum.Value;
			PlayerEXPBaseInitNum.Value = Decimal.Parse(PlayerXML.Element(player).Element("EXP" + PlayerEXPBaseLabel.Text).Element("Init").Value);
			PlayerEXPBaseRateNum.Value = Decimal.Parse(PlayerXML.Element(player).Element("EXP" + PlayerEXPBaseLabel.Text).Element("Rate").Value);
			PlayerEXPBaseNum.Value = PlayerEXPBaseInitNum.Value + (PlayerLevelNum.Value - 1) * PlayerEXPBaseRateNum.Value;
			PlayerEXPGapInitNum.Value = Decimal.Parse(PlayerXML.Element(player).Element("EXP" + PlayerEXPGapLabel.Text).Element("Init").Value);
			PlayerEXPGapRateNum.Value = Decimal.Parse(PlayerXML.Element(player).Element("EXP" + PlayerEXPGapLabel.Text).Element("Rate").Value);
			PlayerEXPGapNum.Value = PlayerEXPGapInitNum.Value + (PlayerLevelNum.Value - 1) * PlayerEXPGapRateNum.Value;
			PlayerEXPNum.Value = PlayerEXPBaseNum.Value * PlayerEXPGapNum.Value;
		}

		private void PlayerAddToXML(string player)
		{
			PlayerXML.Add(new XElement(player,
				new XElement(PlayerHPLabel.Text,
					new XElement("Init", PlayerHPInitNum.Value), new XElement("Rate", PlayerHPRateNum.Value)),
				new XElement(PlayerHP_ReLabel.Text,
					new XElement("Init", PlayerHP_ReInitNum.Value), new XElement("Rate", PlayerHP_ReRateNum.Value)),
				new XElement(PlayerMPLabel.Text,
					new XElement("Init", PlayerMPInitNum.Value), new XElement("Rate", PlayerMPRateNum.Value)),
				new XElement(PlayerMP_ReLabel.Text,
					new XElement("Init", PlayerMP_ReInitNum.Value), new XElement("Rate", PlayerMP_ReRateNum.Value)),
				new XElement(PlayerSPLabel.Text,
					new XElement("Init", PlayerSPInitNum.Value), new XElement("Rate", PlayerSPRateNum.Value)),
				new XElement(PlayerSP_ReLabel.Text,
					new XElement("Init", PlayerSP_ReInitNum.Value), new XElement("Rate", PlayerSP_ReRateNum.Value)),
				new XElement(PlayerSpeedLabel.Text,
					new XElement("Init", PlayerSpeedInitNum.Value), new XElement("Rate", PlayerSpeedRateNum.Value)),
				new XElement(PlayerDMGLabel.Text,
					new XElement("Init", PlayerDMGInitNum.Value), new XElement("Rate", PlayerDMGRateNum.Value)),
				new XElement(PlayerDEFLabel.Text,
					new XElement("Init", PlayerDEFInitNum.Value), new XElement("Rate", PlayerDEFRateNum.Value)),
				new XElement("EXP" + PlayerEXPBaseLabel.Text,
					new XElement("Init", PlayerEXPBaseInitNum.Value), new XElement("Rate", PlayerEXPBaseRateNum.Value)),
				new XElement("EXP" + PlayerEXPGapLabel.Text,
					new XElement("Init", PlayerEXPGapInitNum.Value), new XElement("Rate", PlayerEXPGapRateNum.Value))));

			PlayerSaveXML();
		}
		private void PlayerDeleteFromXML(string player)
		{
			PlayerXML.Element(player).Remove();
			PlayerSaveXML();
		}

		private void PlayerList_SelectedIndexChanged(object sender, EventArgs e)
		{
			if (PlayerList.SelectedIndex == PlayerListLastIndex)
			{
				return;
			}
			if (PlayerList.Items.Count == 0)
			{
				PlayerComponentEnabled(false);
				PlayerDeleteButton.Enabled = false;
				PlayerComponentClear();
				PlayerPreventDataSave = false;
				PlayerIndexLabel.Text = "-";
			}
			else
			{
				if (PlayerList.SelectedIndex != -1)
				{
					PlayerListLastIndex = PlayerList.SelectedIndex;
					PlayerLoadXMLToComponent(PlayerList.GetItemText(PlayerList.Items[PlayerListLastIndex]));
					PlayerComponentEnabled(true);
					PlayerDeleteButton.Enabled = true;
					PlayerPreventDataSave = false;
					PlayerIndexLabel.Text = PlayerListLastIndex.ToString();
				}
			}
		}

		private void PlayerAddButton_Click(object sender, EventArgs e)
		{
			NameInputDialog dialog = new NameInputDialog(PlayerXML);
			if (dialog.ShowDialog() == DialogResult.OK)
			{
				PlayerPreventDataSave = true;
				PlayerList.Select();
				PlayerComponentClear();
				PlayerAddToXML(dialog.ResultText);
				PlayerList.Items.Add(dialog.ResultText);
				PlayerList.SelectedIndex = PlayerList.Items.Count - 1;
				PlayerNameTextBox.Text = dialog.ResultText;
			}
		}
		private void PlayerDeleteButton_Click(object sender, EventArgs e)
		{
			if (MessageBox.Show("Accept to delete this player?", "Message", MessageBoxButtons.YesNo) == DialogResult.Yes)
			{
				PlayerPreventDataSave = true;

				PlayerList.Select();
				PlayerDeleteFromXML(PlayerList.GetItemText(PlayerList.SelectedItem));

				int i = PlayerList.SelectedIndex;
				++PlayerListLastIndex;
				PlayerList.Items.RemoveAt(PlayerList.SelectedIndex);
				PlayerList.SelectedIndex = (PlayerList.Items.Count == i ? --i : i);
			}
		}

		private void PlayerNameTextBox_TextChanged(object sender, EventArgs e)
		{
			if (PlayerList.SelectedIndex == -1 || PlayerNameTextBox.Text == "") return;
			PlayerXML.Element(PlayerList.GetItemText(PlayerList.Items[PlayerList.SelectedIndex])).Name = PlayerNameTextBox.Text;
			PlayerSaveXML();
			PlayerList.Items[PlayerList.SelectedIndex] = PlayerNameTextBox.Text;
			PlayerList.SelectedIndex = PlayerListLastIndex;
		}
		private void PlayerLevelNum_ValueChanged(object sender, EventArgs e)
		{
			PlayerHPNum.Value = Math.Round(PlayerHPInitNum.Value + (PlayerLevelNum.Value - 1) * PlayerHPRateNum.Value);
			PlayerHP_ReNum.Value = Math.Round(PlayerHP_ReInitNum.Value + (PlayerLevelNum.Value - 1) * PlayerHP_ReRateNum.Value);
			PlayerMPNum.Value = Math.Round(PlayerMPInitNum.Value + (PlayerLevelNum.Value - 1) * PlayerMPRateNum.Value);
			PlayerMP_ReNum.Value = Math.Round(PlayerMP_ReInitNum.Value + (PlayerLevelNum.Value - 1) * PlayerMP_ReRateNum.Value);
			PlayerSPNum.Value = Math.Round(PlayerSPInitNum.Value + (PlayerLevelNum.Value - 1) * PlayerSPRateNum.Value);
			PlayerSP_ReNum.Value = Math.Round(PlayerSP_ReInitNum.Value + (PlayerLevelNum.Value - 1) * PlayerSP_ReRateNum.Value);
			PlayerSpeedNum.Value = Math.Round(PlayerSpeedInitNum.Value + (PlayerLevelNum.Value - 1) * PlayerSpeedRateNum.Value);
			PlayerDMGNum.Value = Math.Round(PlayerDMGInitNum.Value + (PlayerLevelNum.Value - 1) * PlayerDMGRateNum.Value);
			PlayerDEFNum.Value = Math.Round(PlayerDEFInitNum.Value + (PlayerLevelNum.Value - 1) * PlayerDEFRateNum.Value);
			PlayerEXPBaseNum.Value = Math.Round(PlayerEXPBaseInitNum.Value + (PlayerLevelNum.Value - 1) * PlayerEXPBaseRateNum.Value);
			PlayerEXPGapNum.Value = Math.Round(PlayerEXPGapInitNum.Value + (PlayerLevelNum.Value - 1) * PlayerEXPGapRateNum.Value);
			PlayerEXPNum.Value = Math.Round(PlayerEXPBaseNum.Value * PlayerEXPGapNum.Value);
		}

		private void PlayerHPInitNum_ValueChanged(object sender, EventArgs e)
		{
			PlayerHPNum.Value = Math.Round(PlayerHPInitNum.Value + (PlayerLevelNum.Value - 1) * PlayerHPRateNum.Value);
			if (PlayerPreventDataSave == true) return;
			PlayerXML.Element(PlayerList.Text).Element(PlayerHPLabel.Text).Element("Init").SetValue(PlayerHPInitNum.Value);
			PlayerSaveXML();
		}
		private void PlayerHPRateNum_ValueChanged(object sender, EventArgs e)
		{
			PlayerHPNum.Value = Math.Round(PlayerHPInitNum.Value + (PlayerLevelNum.Value - 1) * PlayerHPRateNum.Value);
			if (PlayerPreventDataSave == true) return;
			PlayerXML.Element(PlayerList.Text).Element(PlayerHPLabel.Text).Element("Rate").SetValue(PlayerHPRateNum.Value);
			PlayerSaveXML();
		}
		private void PlayerHP_ReInitNum_ValueChanged(object sender, EventArgs e)
		{
			PlayerHP_ReNum.Value = Math.Round(PlayerHP_ReInitNum.Value + (PlayerLevelNum.Value - 1) * PlayerHP_ReRateNum.Value);
			if (PlayerPreventDataSave == true) return;
			PlayerXML.Element(PlayerList.Text).Element(PlayerHP_ReLabel.Text).Element("Init").SetValue(PlayerHP_ReInitNum.Value);
			PlayerSaveXML();
		}
		private void PlayerHP_ReRateNum_ValueChanged(object sender, EventArgs e)
		{
			PlayerHP_ReNum.Value = Math.Round(PlayerHP_ReInitNum.Value + (PlayerLevelNum.Value - 1) * PlayerHP_ReRateNum.Value);
			if (PlayerPreventDataSave == true) return;
			PlayerXML.Element(PlayerList.Text).Element(PlayerHP_ReLabel.Text).Element("Rate").SetValue(PlayerHP_ReRateNum.Value);
			PlayerSaveXML();
		}
		private void PlayerMPInitNum_ValueChanged(object sender, EventArgs e)
		{
			PlayerMPNum.Value = Math.Round(PlayerMPInitNum.Value + (PlayerLevelNum.Value - 1) * PlayerMPRateNum.Value);
			if (PlayerPreventDataSave == true) return;
			PlayerXML.Element(PlayerList.Text).Element(PlayerMPLabel.Text).Element("Init").SetValue(PlayerMPInitNum.Value);
			PlayerSaveXML();
		}
		private void PlayerMPRateNum_ValueChanged(object sender, EventArgs e)
		{
			PlayerMPNum.Value = Math.Round(PlayerMPInitNum.Value + (PlayerLevelNum.Value - 1) * PlayerMPRateNum.Value);
			if (PlayerPreventDataSave == true) return;
			PlayerXML.Element(PlayerList.Text).Element(PlayerMPLabel.Text).Element("Rate").SetValue(PlayerMPRateNum.Value);
			PlayerSaveXML();
		}
		private void PlayerMP_ReInitNum_ValueChanged(object sender, EventArgs e)
		{
			PlayerMP_ReNum.Value = Math.Round(PlayerMP_ReInitNum.Value + (PlayerLevelNum.Value - 1) * PlayerMP_ReRateNum.Value);
			if (PlayerPreventDataSave == true) return;
			PlayerXML.Element(PlayerList.Text).Element(PlayerMP_ReLabel.Text).Element("Init").SetValue(PlayerMP_ReInitNum.Value);
			PlayerSaveXML();
		}
		private void PlayerMP_ReRateNum_ValueChanged(object sender, EventArgs e)
		{
			PlayerMP_ReNum.Value = Math.Round(PlayerMP_ReInitNum.Value + (PlayerLevelNum.Value - 1) * PlayerMP_ReRateNum.Value);
			if (PlayerPreventDataSave == true) return;
			PlayerXML.Element(PlayerList.Text).Element(PlayerMP_ReLabel.Text).Element("Rate").SetValue(PlayerMP_ReRateNum.Value);
			PlayerSaveXML();
		}
		private void PlayerSPInitNum_ValueChanged(object sender, EventArgs e)
		{
			PlayerSPNum.Value = Math.Round(PlayerSPInitNum.Value + (PlayerLevelNum.Value - 1) * PlayerSPRateNum.Value);
			if (PlayerPreventDataSave == true) return;
			PlayerXML.Element(PlayerList.Text).Element(PlayerSPLabel.Text).Element("Init").SetValue(PlayerSPInitNum.Value);
			PlayerSaveXML();
		}
		private void PlayerSPRateNum_ValueChanged(object sender, EventArgs e)
		{
			PlayerSPNum.Value = Math.Round(PlayerSPInitNum.Value + (PlayerLevelNum.Value - 1) * PlayerSPRateNum.Value);
			if (PlayerPreventDataSave == true) return;
			PlayerXML.Element(PlayerList.Text).Element(PlayerSPLabel.Text).Element("Rate").SetValue(PlayerSPRateNum.Value);
			PlayerSaveXML();
		}
		private void PlayerSP_ReInitNum_ValueChanged(object sender, EventArgs e)
		{
			PlayerSP_ReNum.Value = Math.Round(PlayerSP_ReInitNum.Value + (PlayerLevelNum.Value - 1) * PlayerSP_ReRateNum.Value);
			if (PlayerPreventDataSave == true) return;
			PlayerXML.Element(PlayerList.Text).Element(PlayerSP_ReLabel.Text).Element("Init").SetValue(PlayerSP_ReInitNum.Value);
			PlayerSaveXML();
		}
		private void PlayerSP_ReRateNum_ValueChanged(object sender, EventArgs e)
		{
			PlayerSP_ReNum.Value = Math.Round(PlayerSP_ReInitNum.Value + (PlayerLevelNum.Value - 1) * PlayerSP_ReRateNum.Value);
			if (PlayerPreventDataSave == true) return;
			PlayerXML.Element(PlayerList.Text).Element(PlayerSP_ReLabel.Text).Element("Rate").SetValue(PlayerSP_ReRateNum.Value);
			PlayerSaveXML();
		}
		private void PlayerSpeedInitNum_ValueChanged(object sender, EventArgs e)
		{
			PlayerSpeedNum.Value = Math.Round(PlayerSpeedInitNum.Value + (PlayerLevelNum.Value - 1) * PlayerSpeedRateNum.Value);
			if (PlayerPreventDataSave == true) return;
			PlayerXML.Element(PlayerList.Text).Element(PlayerSpeedLabel.Text).Element("Init").SetValue(PlayerSpeedInitNum.Value);
			PlayerSaveXML();
		}
		private void PlayerSpeedRateNum_ValueChanged(object sender, EventArgs e)
		{
			PlayerSpeedNum.Value = Math.Round(PlayerSpeedInitNum.Value + (PlayerLevelNum.Value - 1) * PlayerSpeedRateNum.Value);
			if (PlayerPreventDataSave == true) return;
			PlayerXML.Element(PlayerList.Text).Element(PlayerSpeedLabel.Text).Element("Rate").SetValue(PlayerSpeedRateNum.Value);
			PlayerSaveXML();
		}
		private void PlayerDMGInitNum_ValueChanged(object sender, EventArgs e)
		{
			PlayerDMGNum.Value = Math.Round(PlayerDMGInitNum.Value + (PlayerLevelNum.Value - 1) * PlayerDMGRateNum.Value);
			if (PlayerPreventDataSave == true) return;
			PlayerXML.Element(PlayerList.Text).Element(PlayerDMGLabel.Text).Element("Init").SetValue(PlayerDMGInitNum.Value);
			PlayerSaveXML();
		}
		private void PlayerDMGRateNum_ValueChanged(object sender, EventArgs e)
		{
			PlayerDMGNum.Value = Math.Round(PlayerDMGInitNum.Value + (PlayerLevelNum.Value - 1) * PlayerDMGRateNum.Value);
			if (PlayerPreventDataSave == true) return;
			PlayerXML.Element(PlayerList.Text).Element(PlayerDMGLabel.Text).Element("Rate").SetValue(PlayerDMGRateNum.Value);
			PlayerSaveXML();
		}
		private void PlayerDEFInitNum_ValueChanged(object sender, EventArgs e)
		{
			PlayerDEFNum.Value = Math.Round(PlayerDEFInitNum.Value + (PlayerLevelNum.Value - 1) * PlayerDEFRateNum.Value);
			if (PlayerPreventDataSave == true) return;
			PlayerXML.Element(PlayerList.Text).Element(PlayerDEFLabel.Text).Element("Init").SetValue(PlayerDEFInitNum.Value);
			PlayerSaveXML();
		}
		private void PlayerDEFRateNum_ValueChanged(object sender, EventArgs e)
		{
			PlayerDEFNum.Value = Math.Round(PlayerDEFInitNum.Value + (PlayerLevelNum.Value - 1) * PlayerDEFRateNum.Value);
			if (PlayerPreventDataSave == true) return;
			PlayerXML.Element(PlayerList.Text).Element(PlayerDEFLabel.Text).Element("Rate").SetValue(PlayerDEFRateNum.Value);
			PlayerSaveXML();
		}
		private void PlayerEXPBaseInitNum_ValueChanged(object sender, EventArgs e)
		{
			PlayerEXPBaseNum.Value = Math.Round(PlayerEXPBaseInitNum.Value + (PlayerLevelNum.Value - 1) * PlayerEXPBaseRateNum.Value);
			PlayerEXPNum.Value = Math.Round(PlayerEXPBaseNum.Value * PlayerEXPGapNum.Value);
			if (PlayerPreventDataSave == true) return;
			PlayerXML.Element(PlayerList.Text).Element("EXP" + PlayerEXPBaseLabel.Text).Element("Init").SetValue(PlayerEXPBaseInitNum.Value);
			PlayerSaveXML();
		}
		private void PlayerEXPBaseRateNum_ValueChanged(object sender, EventArgs e)
		{
			PlayerEXPBaseNum.Value = Math.Round(PlayerEXPBaseInitNum.Value + (PlayerLevelNum.Value - 1) * PlayerEXPBaseRateNum.Value);
			PlayerEXPNum.Value = Math.Round(PlayerEXPBaseNum.Value * PlayerEXPGapNum.Value);
			if (PlayerPreventDataSave == true) return;
			PlayerXML.Element(PlayerList.Text).Element("EXP" + PlayerEXPBaseLabel.Text).Element("Rate").SetValue(PlayerEXPBaseRateNum.Value);
			PlayerSaveXML();
		}
		private void PlayerEXPGapInitNum_ValueChanged(object sender, EventArgs e)
		{
			PlayerEXPGapNum.Value = Math.Round(PlayerEXPGapInitNum.Value + (PlayerLevelNum.Value - 1) * PlayerEXPGapRateNum.Value);
			PlayerEXPNum.Value = Math.Round(PlayerEXPBaseNum.Value * PlayerEXPGapNum.Value);
			if (PlayerPreventDataSave == true) return;
			PlayerXML.Element(PlayerList.Text).Element("EXP" + PlayerEXPGapLabel.Text).Element("Init").SetValue(PlayerEXPGapInitNum.Value);
			PlayerSaveXML();
		}
		private void PlayerEXPGapRateNum_ValueChanged(object sender, EventArgs e)
		{
			PlayerEXPGapNum.Value = Math.Round(PlayerEXPGapInitNum.Value + (PlayerLevelNum.Value - 1) * PlayerEXPGapRateNum.Value);
			PlayerEXPNum.Value = Math.Round(PlayerEXPBaseNum.Value * PlayerEXPGapNum.Value);
			if (PlayerPreventDataSave == true) return;
			PlayerXML.Element(PlayerList.Text).Element("EXP" + PlayerEXPGapLabel.Text).Element("Rate").SetValue(PlayerEXPGapRateNum.Value);
			PlayerSaveXML();
		}

		#endregion Player Tab

		#region Enemy Tab

		private int EnemyListLastIndex;
		private bool EnemyPreventDataSave = false;

		private void EnemySaveXML()
		{
			EnemyXML.Save("Enemies.xml");
		}
		private void EnemyComponentClear()
		{
			EnemyNameTextBox.Text = "";
			EnemyLevelNum.Value = 1;
			EnemyRankNum.Value = 1;

			EnemyHPNum.Value = 0;
			EnemyHP_ReNum.Value = 0;
			EnemyMPNum.Value = 0;
			EnemyMP_ReNum.Value = 0;
			EnemySPNum.Value = 0;
			EnemySP_ReNum.Value = 0;
			EnemySpeedNum.Value = 0;
			EnemyDMGNum.Value = 0;
			EnemyDEFNum.Value = 0;
			EnemyGoldNum.Value = 0;
			EnemyEXPNum.Value = 0;

			EnemyItemTextBox.Text = "";
			EnemyArmorTextBox.Text = "";
			EnemyWeaponTextBox.Text = "";
		}
		private void EnemyComponentEnabled(bool b)
		{
			EnemyNameTextBox.Enabled = b;
			EnemyLevelNum.Enabled = b;
			EnemyRankNum.Enabled = b;
			EnemyHPNum.Enabled = b;
			EnemyHP_ReNum.Enabled = b;
			EnemyMPNum.Enabled = b;
			EnemyMP_ReNum.Enabled = b;
			EnemySPNum.Enabled = b;
			EnemySP_ReNum.Enabled = b;
			EnemySpeedNum.Enabled = b;
			EnemyDMGNum.Enabled = b;
			EnemyDEFNum.Enabled = b;
			EnemyGoldNum.Enabled = b;
			EnemyEXPNum.Enabled = b;
			EnemyItemTextBox.Enabled = b;
			EnemyArmorTextBox.Enabled = b;
			EnemyWeaponTextBox.Enabled = b;
		}
		private void EnemyLoadXMLToComponent(string enemy)
		{
			EnemyNameTextBox.Text = enemy;
			EnemyLevelNum.Value = Decimal.Parse(EnemyXML.Element(enemy).Element(EnemyLevelLabel.Text).Value);
			EnemyRankNum.Value = Decimal.Parse(EnemyXML.Element(enemy).Element(EnemyRankLabel.Text).Value);

			EnemyHPNum.Value = Decimal.Parse(EnemyXML.Element(enemy).Element(EnemyHPLabel.Text).Value);
			EnemyHP_ReNum.Value = Decimal.Parse(EnemyXML.Element(enemy).Element(EnemyHP_ReLabel.Text).Value);
			EnemyMPNum.Value = Decimal.Parse(EnemyXML.Element(enemy).Element(EnemyMPLabel.Text).Value);
			EnemyMP_ReNum.Value = Decimal.Parse(EnemyXML.Element(enemy).Element(EnemyMP_ReLabel.Text).Value);
			EnemySPNum.Value = Decimal.Parse(EnemyXML.Element(enemy).Element(EnemySPLabel.Text).Value);
			EnemySP_ReNum.Value = Decimal.Parse(EnemyXML.Element(enemy).Element(EnemySP_ReLabel.Text).Value);
			EnemySpeedNum.Value = Decimal.Parse(EnemyXML.Element(enemy).Element(EnemySpeedLabel.Text).Value);
			EnemyDMGNum.Value = Decimal.Parse(EnemyXML.Element(enemy).Element(EnemyDMGLabel.Text).Value);
			EnemyDEFNum.Value = Decimal.Parse(EnemyXML.Element(enemy).Element(EnemyDEFLabel.Text).Value);
			EnemyEXPNum.Value = Decimal.Parse(EnemyXML.Element(enemy).Element(EnemyEXPLabel.Text).Value);

			EnemyItemTextBox.Text = EnemyXML.Element(enemy).Element(EnemyItemLabel.Text).Value;
			EnemyArmorTextBox.Text = EnemyXML.Element(enemy).Element(EnemyArmorLabel.Text).Value;
			EnemyWeaponTextBox.Text = EnemyXML.Element(enemy).Element(EnemyWeaponLabel.Text).Value;
		}

		private void EnemyAddToXML(string enemy)
		{
			EnemyXML.Add(new XElement(enemy,
				new XElement(EnemyLevelLabel.Text, EnemyLevelNum.Value),
				new XElement(EnemyRankLabel.Text, EnemyRankNum.Value),
				new XElement(EnemyHPLabel.Text, EnemyHPNum.Value),
				new XElement(EnemyHP_ReLabel.Text, EnemyHP_ReNum.Value),
				new XElement(EnemyMPLabel.Text, EnemyMPNum.Value),
				new XElement(EnemyMP_ReLabel.Text, EnemyMP_ReNum.Value),
				new XElement(EnemySPLabel.Text, EnemySPNum.Value),
				new XElement(EnemySP_ReLabel.Text, EnemySP_ReNum.Value),
				new XElement(EnemySpeedLabel.Text, EnemySpeedNum.Value),
				new XElement(EnemyDMGLabel.Text, EnemyDMGNum.Value),
				new XElement(EnemyDEFLabel.Text, EnemyDEFNum.Value),
				new XElement(EnemyGoldLabel.Text, EnemyGoldNum.Value),
				new XElement(EnemyEXPLabel.Text, EnemyEXPNum.Value),
				new XElement(EnemyItemLabel.Text, EnemyItemTextBox.Text),
				new XElement(EnemyArmorLabel.Text, EnemyArmorTextBox.Text),
				new XElement(EnemyWeaponLabel.Text, EnemyWeaponTextBox.Text)));

			EnemySaveXML();
		}
		private void EnemyDeleteFromXML(string enemy)
		{
			EnemyXML.Element(enemy).Remove();
			EnemySaveXML();
		}

		private void EnemyList_SelectedIndexChanged(object sender, EventArgs e)
		{
			if (EnemyList.SelectedIndex == EnemyListLastIndex)
			{
				return;
			}
			if (EnemyList.Items.Count == 0)
			{
				EnemyComponentEnabled(false);
				EnemyDeleteButton.Enabled = false;
				EnemyComponentClear();
				EnemyPreventDataSave = false;
				EnemyIndexLabel.Text = "-";
			}
			else
			{
				if (EnemyList.SelectedIndex != -1)
				{
					EnemyListLastIndex = EnemyList.SelectedIndex;
					EnemyLoadXMLToComponent(EnemyList.GetItemText(EnemyList.Items[EnemyListLastIndex]));
					EnemyComponentEnabled(true);
					EnemyDeleteButton.Enabled = true;
					EnemyPreventDataSave = false;
					EnemyIndexLabel.Text = EnemyListLastIndex.ToString();
				}
			}
		}

		private void EnemyAddButton_Click(object sender, EventArgs e)
		{
			NameInputDialog dialog = new NameInputDialog(EnemyXML);
			if (dialog.ShowDialog() == DialogResult.OK)
			{
				EnemyPreventDataSave = true;
				EnemyList.Select();
				EnemyComponentClear();
				EnemyAddToXML(dialog.ResultText);
				EnemyList.Items.Add(dialog.ResultText);
				EnemyList.SelectedIndex = EnemyList.Items.Count - 1;
				EnemyNameTextBox.Text = dialog.ResultText;
			}
		}
		private void EnemyDeleteButton_Click(object sender, EventArgs e)
		{
			if (MessageBox.Show("Accept to delete this enemy?", "Message", MessageBoxButtons.YesNo) == DialogResult.Yes)
			{
				EnemyPreventDataSave = true;

				EnemyList.Select();
				EnemyDeleteFromXML(EnemyList.GetItemText(EnemyList.SelectedItem));

				int i = EnemyList.SelectedIndex;
				++EnemyListLastIndex;
				EnemyList.Items.RemoveAt(EnemyList.SelectedIndex);
				EnemyList.SelectedIndex = (EnemyList.Items.Count == i ? --i : i);
			}
		}

		private void EnemyNameTextBox_TextChanged(object sender, EventArgs e)
		{
			if (EnemyList.SelectedIndex == -1 || EnemyNameTextBox.Text == "") return;
			EnemyXML.Element(EnemyList.GetItemText(EnemyList.Items[EnemyList.SelectedIndex])).Name = EnemyNameTextBox.Text;
			EnemySaveXML();
			EnemyList.Items[EnemyList.SelectedIndex] = EnemyNameTextBox.Text;
			EnemyList.SelectedIndex = EnemyListLastIndex;
		}

		private void EnemyLevelNum_ValueChanged(object sender, EventArgs e)
		{
			if (EnemyPreventDataSave == true) return;
			EnemyXML.Element(EnemyList.Text).Element(EnemyLevelLabel.Text).SetValue(EnemyLevelNum.Value);
			EnemySaveXML();
		}
		private void EnemyRankNum_ValueChanged(object sender, EventArgs e)
		{
			if (EnemyPreventDataSave == true) return;
			EnemyXML.Element(EnemyList.Text).Element(EnemyRankLabel.Text).SetValue(EnemyRankNum.Value);
			EnemySaveXML();
		}
		private void EnemyHPNum_ValueChanged(object sender, EventArgs e)
		{
			if (EnemyPreventDataSave == true) return;
			EnemyXML.Element(EnemyList.Text).Element(EnemyHPLabel.Text).SetValue(EnemyHPNum.Value);
			EnemySaveXML();
		}
		private void EnemyHP_ReNum_ValueChanged(object sender, EventArgs e)
		{
			if (EnemyPreventDataSave == true) return;
			EnemyXML.Element(EnemyList.Text).Element(EnemyHP_ReLabel.Text).SetValue(EnemyHP_ReNum.Value);
			EnemySaveXML();
		}
		private void EnemyMPNum_ValueChanged(object sender, EventArgs e)
		{
			if (EnemyPreventDataSave == true) return;
			EnemyXML.Element(EnemyList.Text).Element(EnemyMPLabel.Text).SetValue(EnemyMPNum.Value);
			EnemySaveXML();
		}
		private void EnemyMP_ReNum_ValueChanged(object sender, EventArgs e)
		{
			if (EnemyPreventDataSave == true) return;
			EnemyXML.Element(EnemyList.Text).Element(EnemyMP_ReLabel.Text).SetValue(EnemyMP_ReNum.Value);
			EnemySaveXML();
		}
		private void EnemySPNum_ValueChanged(object sender, EventArgs e)
		{
			if (EnemyPreventDataSave == true) return;
			EnemyXML.Element(EnemyList.Text).Element(EnemySPLabel.Text).SetValue(EnemySPNum.Value);
			EnemySaveXML();
		}
		private void EnemySP_ReNum_ValueChanged(object sender, EventArgs e)
		{
			if (EnemyPreventDataSave == true) return;
			EnemyXML.Element(EnemyList.Text).Element(EnemySP_ReLabel.Text).SetValue(EnemySP_ReNum.Value);
			EnemySaveXML();
		}
		private void EnemySpeedNum_ValueChanged(object sender, EventArgs e)
		{
			if (EnemyPreventDataSave == true) return;
			EnemyXML.Element(EnemyList.Text).Element(EnemySpeedLabel.Text).SetValue(EnemySpeedNum.Value);
			EnemySaveXML();
		}
		private void EnemyDMGNum_ValueChanged(object sender, EventArgs e)
		{
			if (EnemyPreventDataSave == true) return;
			EnemyXML.Element(EnemyList.Text).Element(EnemyDMGLabel.Text).SetValue(EnemyDMGNum.Value);
			EnemySaveXML();
		}
		private void EnemyDEFNum_ValueChanged(object sender, EventArgs e)
		{
			if (EnemyPreventDataSave == true) return;
			EnemyXML.Element(EnemyList.Text).Element(EnemyDEFLabel.Text).SetValue(EnemyDEFNum.Value);
			EnemySaveXML();
		}
		private void EnemyGoldNum_ValueChanged(object sender, EventArgs e)
		{
			if (EnemyPreventDataSave == true) return;
			EnemyXML.Element(EnemyList.Text).Element(EnemyGoldLabel.Text).SetValue(EnemyGoldNum.Value);
			EnemySaveXML();
		}
		private void EnemyEXPNum_ValueChanged(object sender, EventArgs e)
		{
			if (EnemyPreventDataSave == true) return;
			EnemyXML.Element(EnemyList.Text).Element(EnemyEXPLabel.Text).SetValue(EnemyEXPNum.Value);
			EnemySaveXML();
		}
		private void EnemyItemTextBox_TextChanged(object sender, EventArgs e)
		{
			if (EnemyPreventDataSave == true) return;
			EnemyXML.Element(EnemyList.Text).Element(EnemyItemLabel.Text).SetValue(EnemyItemTextBox.Text);
			EnemySaveXML();
		}
		private void EnemyArmorTextBox_TextChanged(object sender, EventArgs e)
		{
			if (EnemyPreventDataSave == true) return;
			EnemyXML.Element(EnemyList.Text).Element(EnemyArmorLabel.Text).SetValue(EnemyArmorTextBox.Text);
			EnemySaveXML();
		}
		private void EnemyWeaponTextBox_TextChanged(object sender, EventArgs e)
		{
			if (EnemyPreventDataSave == true) return;
			EnemyXML.Element(EnemyList.Text).Element(EnemyWeaponLabel.Text).SetValue(EnemyWeaponTextBox.Text);
			EnemySaveXML();
		}

		#endregion Enemy Tab

		#region Token Tab

		public static string[] TokenBuffItems = new string[] {
			"Invincible", "Dual Casting", "Hiding", "Shield", "Barrier"
		};
		public static string[] TokenDebuffItems = new string[] {
			"EnemyDEF", "DoT", "Slow", "Stun"
		};

		private int TokenListLastIndex;
		private bool TokenPreventDataSave = false;

		private void TokenSaveXML()
		{
			TokenXML.Save("Tokens.xml");
		}
		private void TokenComponentClear()
		{
			TokenNameTextBox.Text = "";
			TokenClassComboBox.SelectedIndex = 0;

			TokenDMGNum1.Value = 0;
			TokenDMGNum2.Value = 0;
			TokenDMGTurnNum.Value = 0;
			TokenSTANum1.Value = 0;
			TokenSTANum2.Value = 0;
			TokenSTATurnNum.Value = 0;
			TokenSTA_ReNum1.Value = 0;
			TokenSTA_ReNum2.Value = 0;
			TokenSTA_ReTargetComboBox.SelectedIndex = 0;
			TokenSTA_ReTurnNum.Value = 0;
			TokenDEFNum1.Value = 0;
			TokenDEFNum2.Value = 0;
			TokenDEFTargetComboBox.SelectedIndex = 0;
			TokenDEFTurnNum.Value = 0;
			TokenHPNum1.Value = 0;
			TokenHPNum2.Value = 0;
			TokenHPTargetComboBox.SelectedIndex = 0;
			TokenHPTurnNum.Value = 0;
			TokenMPNum1.Value = 0;
			TokenMPNum2.Value = 0;
			TokenMPTurnNum.Value = 0;
			TokenHPStealNum1.Value = 0;
			TokenHPStealNum2.Value = 0;
			TokenHPStealTargetComboBox.SelectedIndex = 0;
			TokenHPStealTurnNum.Value = 0;
			TokenSpeedNum1.Value = 0;
			TokenSpeedNum2.Value = 0;
			TokenSpeedTargetComboBox.SelectedIndex = 0;
			TokenSpeedTurnNum.Value = 0;
			TokenDMGBuffNum1.Value = 0;
			TokenDMGBuffNum2.Value = 0;
			TokenDMGBuffTargetComboBox.SelectedIndex = 0;
			TokenDMGBuffTurnNum.Value = 0;
			TokenBuffList.Items.Clear();
			TokenDebuffList.Items.Clear();
		}
		private void TokenComponentEnabled(bool b)
		{
			TokenNameTextBox.Enabled = b;
			TokenClassComboBox.Enabled = b;
			TokenDMGNum1.Enabled = b;
			TokenDMGNum2.Enabled = b;
			TokenDMGTurnNum.Enabled = b;
			TokenSTANum1.Enabled = b;
			TokenSTANum2.Enabled = b;
			TokenSTATurnNum.Enabled = b;
			TokenSTA_ReNum1.Enabled = b;
			TokenSTA_ReNum2.Enabled = b;
			TokenSTA_ReTargetComboBox.Enabled = b;
			TokenSTA_ReTurnNum.Enabled = b;
			TokenDEFNum1.Enabled = b;
			TokenDEFNum2.Enabled = b;
			TokenDEFTargetComboBox.Enabled = b;
			TokenDEFTurnNum.Enabled = b;
			TokenHPNum1.Enabled = b;
			TokenHPNum2.Enabled = b;
			TokenHPTargetComboBox.Enabled = b;
			TokenHPTurnNum.Enabled = b;
			TokenMPNum1.Enabled = b;
			TokenMPNum2.Enabled = b;
			TokenMPTurnNum.Enabled = b;
			TokenHPStealNum1.Enabled = b;
			TokenHPStealNum2.Enabled = b;
			TokenHPStealTargetComboBox.Enabled = b;
			TokenHPStealTurnNum.Enabled = b;
			TokenSpeedNum1.Enabled = b;
			TokenSpeedNum2.Enabled = b;
			TokenSpeedTargetComboBox.Enabled = b;
			TokenSpeedTurnNum.Enabled = b;
			TokenDMGBuffNum1.Enabled = b;
			TokenDMGBuffNum2.Enabled = b;
			TokenDMGBuffTargetComboBox.Enabled = b;
			TokenDMGBuffTurnNum.Enabled = b;
			TokenBuffList.Enabled = b;
			TokenBuffAddButton.Enabled = b;
			TokenDebuffList.Enabled = b;
			TokenDebuffAddButton.Enabled = b;
		}
		private void TokenLoadXMLToComponent(string token)
		{
			TokenNameTextBox.Text = token;
			TokenClassComboBox.SelectedIndex = Int32.Parse(TokenXML.Element(token).Element(TokenClassLabel.Text).Value);

			TokenDMGNum1.Value = Decimal.Parse(TokenXML.Element(token).Element(TokenDMGLabel.Text).Element("Num1").Value);
			TokenDMGNum2.Value = Decimal.Parse(TokenXML.Element(token).Element(TokenDMGLabel.Text).Element("Num2").Value);
			TokenDMGTurnNum.Value = Decimal.Parse(TokenXML.Element(token).Element(TokenDMGLabel.Text).Element("Turn").Value);
			TokenSTANum1.Value = Decimal.Parse(TokenXML.Element(token).Element(TokenSPLabel.Text).Element("Num1").Value);
			TokenSTANum2.Value = Decimal.Parse(TokenXML.Element(token).Element(TokenSPLabel.Text).Element("Num2").Value);
			TokenSTATurnNum.Value = Decimal.Parse(TokenXML.Element(token).Element(TokenSPLabel.Text).Element("Turn").Value);
			TokenSTA_ReNum1.Value = Decimal.Parse(TokenXML.Element(token).Element(TokenSP_ReLabel.Text).Element("Num1").Value);
			TokenSTA_ReNum2.Value = Decimal.Parse(TokenXML.Element(token).Element(TokenSP_ReLabel.Text).Element("Num2").Value);
			TokenSTA_ReTargetComboBox.SelectedIndex = Int32.Parse(TokenXML.Element(token).Element(TokenSP_ReLabel.Text).Element("Target").Value);
			TokenSTA_ReTurnNum.Value = Decimal.Parse(TokenXML.Element(token).Element(TokenSP_ReLabel.Text).Element("Turn").Value);
			TokenDEFNum1.Value = Decimal.Parse(TokenXML.Element(token).Element(TokenDEFLabel.Text).Element("Num1").Value);
			TokenDEFNum2.Value = Decimal.Parse(TokenXML.Element(token).Element(TokenDEFLabel.Text).Element("Num2").Value);
			TokenDEFTargetComboBox.SelectedIndex = Int32.Parse(TokenXML.Element(token).Element(TokenDEFLabel.Text).Element("Target").Value);
			TokenDEFTurnNum.Value = Decimal.Parse(TokenXML.Element(token).Element(TokenDEFLabel.Text).Element("Turn").Value);
			TokenHPNum1.Value = Decimal.Parse(TokenXML.Element(token).Element(TokenHPLabel.Text).Element("Num1").Value);
			TokenHPNum2.Value = Decimal.Parse(TokenXML.Element(token).Element(TokenHPLabel.Text).Element("Num2").Value);
			TokenHPTargetComboBox.SelectedIndex = Int32.Parse(TokenXML.Element(token).Element(TokenHPLabel.Text).Element("Target").Value);
			TokenHPTurnNum.Value = Decimal.Parse(TokenXML.Element(token).Element(TokenHPLabel.Text).Element("Turn").Value);
			TokenMPNum1.Value = Decimal.Parse(TokenXML.Element(token).Element(TokenMPLabel.Text).Element("Num1").Value);
			TokenMPNum2.Value = Decimal.Parse(TokenXML.Element(token).Element(TokenMPLabel.Text).Element("Num2").Value);
			TokenMPTurnNum.Value = Decimal.Parse(TokenXML.Element(token).Element(TokenMPLabel.Text).Element("Turn").Value);
			TokenHPStealNum1.Value = Decimal.Parse(TokenXML.Element(token).Element(TokenHPStealLabel.Text).Element("Num1").Value);
			TokenHPStealNum2.Value = Decimal.Parse(TokenXML.Element(token).Element(TokenHPStealLabel.Text).Element("Num2").Value);
			TokenHPStealTargetComboBox.SelectedIndex = Int32.Parse(TokenXML.Element(token).Element(TokenHPStealLabel.Text).Element("Target").Value);
			TokenHPStealTurnNum.Value = Decimal.Parse(TokenXML.Element(token).Element(TokenHPStealLabel.Text).Element("Turn").Value);
			TokenSpeedNum1.Value = Decimal.Parse(TokenXML.Element(token).Element(TokenSpeedLabel.Text).Element("Num1").Value);
			TokenSpeedNum2.Value = Decimal.Parse(TokenXML.Element(token).Element(TokenSpeedLabel.Text).Element("Num2").Value);
			TokenSpeedTargetComboBox.SelectedIndex = Int32.Parse(TokenXML.Element(token).Element(TokenSpeedLabel.Text).Element("Target").Value);
			TokenSpeedTurnNum.Value = Decimal.Parse(TokenXML.Element(token).Element(TokenSpeedLabel.Text).Element("Turn").Value);
			TokenDMGBuffNum1.Value = Decimal.Parse(TokenXML.Element(token).Element(TokenDMGBuffLabel.Text).Element("Num1").Value);
			TokenDMGBuffNum2.Value = Decimal.Parse(TokenXML.Element(token).Element(TokenDMGBuffLabel.Text).Element("Num2").Value);
			TokenDMGBuffTargetComboBox.SelectedIndex = Int32.Parse(TokenXML.Element(token).Element(TokenDMGBuffLabel.Text).Element("Target").Value);
			TokenDMGBuffTurnNum.Value = Decimal.Parse(TokenXML.Element(token).Element(TokenDMGBuffLabel.Text).Element("Turn").Value);

			TokenBuffList.Items.Clear();
			TokenDebuffList.Items.Clear();
			TokenPropertyItem item;
			IEnumerable children = TokenXML.Element(token).Element(TokenBuffLabel.Text).Elements();
			foreach(XElement x in children)
			{
				item = new TokenPropertyItem();
				item.text = x.Name.ToString();
				item.num1 = Int16.Parse(x.Element("Num1").Value);
				item.num2 = Int16.Parse(x.Element("Num2").Value);
				item.target = (TokenTarget)Int16.Parse(x.Element("Target").Value);
				item.turn = UInt16.Parse(x.Element("Turn").Value);
				TokenBuffList.Items.Add(item);
			}
			children = TokenXML.Element(token).Element(TokenDebuffLabel.Text).Elements();
			foreach (XElement x in children)
			{
				item = new TokenPropertyItem();
				item.text = x.Name.ToString();
				item.num1 = Int16.Parse(x.Element("Num1").Value);
				item.num2 = Int16.Parse(x.Element("Num2").Value);
				item.target = (TokenTarget)Int16.Parse(x.Element("Target").Value);
				item.turn = UInt16.Parse(x.Element("Turn").Value);
				TokenDebuffList.Items.Add(item);
			}

			if (TokenBuffList.Items.Count > 0)
			{
				TokenBuffList.SelectedIndex = 0;
			}
			if (TokenDebuffList.Items.Count > 0)
			{
				TokenDebuffList.SelectedIndex = 0;
			}
		}

		private void TokenAddToXML(string token)
		{
			TokenXML.Add(new XElement(token,
				new XElement(TokenClassLabel.Text, TokenClassComboBox.SelectedIndex),
				new XElement(TokenDMGLabel.Text, 
					new XElement("Num1", TokenDMGNum1.Value),
					new XElement("Num2", TokenDMGNum2.Value),
					new XElement("Turn", TokenDMGTurnNum.Value)),
				new XElement(TokenSPLabel.Text,
					new XElement("Num1", TokenSTANum1.Value),
					new XElement("Num2", TokenSTANum2.Value),
					new XElement("Turn", TokenSTATurnNum.Value)),
				new XElement(TokenSP_ReLabel.Text,
					new XElement("Num1", TokenSTA_ReNum1.Value),
					new XElement("Num2", TokenSTA_ReNum2.Value),
					new XElement("Target", TokenSTA_ReTargetComboBox.SelectedIndex),
					new XElement("Turn", TokenSTA_ReTurnNum.Value)),
				new XElement(TokenDEFLabel.Text,
					new XElement("Num1", TokenDEFNum1.Value),
					new XElement("Num2", TokenDEFNum2.Value),
					new XElement("Target", TokenDEFTargetComboBox.SelectedIndex),
					new XElement("Turn", TokenDEFTurnNum.Value)),
				new XElement(TokenHPLabel.Text,
					new XElement("Num1", TokenHPNum1.Value),
					new XElement("Num2", TokenHPNum2.Value),
					new XElement("Target", TokenHPTargetComboBox.SelectedIndex),
					new XElement("Turn", TokenHPTurnNum.Value)),
				new XElement(TokenMPLabel.Text,
					new XElement("Num1", TokenMPNum1.Value),
					new XElement("Num2", TokenMPNum2.Value),
					new XElement("Turn", TokenMPTurnNum.Value)),
				new XElement(TokenHPStealLabel.Text,
					new XElement("Num1", TokenHPStealNum1.Value),
					new XElement("Num2", TokenHPStealNum2.Value),
					new XElement("Target", TokenHPStealTargetComboBox.SelectedIndex),
					new XElement("Turn", TokenHPStealTurnNum.Value)),
				new XElement(TokenSpeedLabel.Text,
					new XElement("Num1", TokenSpeedNum1.Value),
					new XElement("Num2", TokenSpeedNum2.Value),
					new XElement("Target", TokenSpeedTargetComboBox.SelectedIndex),
					new XElement("Turn", TokenSpeedTurnNum.Value)),
				new XElement(TokenDMGBuffLabel.Text,
					new XElement("Num1", TokenDMGBuffNum1.Value),
					new XElement("Num2", TokenDMGBuffNum2.Value),
					new XElement("Target", TokenDMGBuffTargetComboBox.SelectedIndex),
					new XElement("Turn", TokenDMGBuffTurnNum.Value)),
				new XElement(TokenBuffLabel.Text), new XElement(TokenDebuffLabel.Text)));
			
			foreach (TokenPropertyItem t in TokenBuffList.Items)
			{
				TokenXML.Element(token).Element(TokenBuffLabel.Text).Add(
					new XElement(t.text,
						new XElement("Num1", t.num1),
						new XElement("Num2", t.num2),
						new XElement("Target", (short)t.target),
						new XElement("Turn", t.turn)));
			}

			TokenSaveXML();
		}
		private void TokenDeleteFromXML(string token)
		{
			TokenXML.Element(token).Remove();
			TokenSaveXML();
		}

		private void TokenList_SelectedIndexChanged(object sender, EventArgs e)
		{
			if (TokenList.SelectedIndex == TokenListLastIndex)
			{
				return;
			}
			if (TokenList.Items.Count == 0)
			{
				TokenComponentEnabled(false);
				TokenDeleteButton.Enabled = false;
				TokenBuffEditButton.Enabled = false;
				TokenBuffDeleteButton.Enabled = false;
				TokenDebuffEditButton.Enabled = false;
				TokenDebuffDeleteButton.Enabled = false;
				TokenComponentClear();
				TokenPreventDataSave = false;
				TokenIndexLabel.Text = "-";
				TokenClassIndexLabel.Text = "0";
			}
			else
			{
				if (TokenList.SelectedIndex != -1)
				{
					TokenListLastIndex = TokenList.SelectedIndex;
					TokenLoadXMLToComponent(TokenList.GetItemText(TokenList.Items[TokenListLastIndex]));
					TokenComponentEnabled(true);
					TokenDeleteButton.Enabled = true;
					TokenPreventDataSave = false;
					TokenIndexLabel.Text = TokenListLastIndex.ToString();
				}
			}
		}

		private void TokenAddButton_Click(object sender, EventArgs e)
		{
			NameInputDialog dialog = new NameInputDialog(TokenXML);
			if (dialog.ShowDialog() == DialogResult.OK)
			{
				TokenPreventDataSave = true;
				TokenList.Select();
				TokenComponentClear();
				TokenAddToXML(dialog.ResultText);
				TokenList.Items.Add(dialog.ResultText);
				TokenList.SelectedIndex = TokenList.Items.Count - 1;
				TokenNameTextBox.Text = dialog.ResultText;
			}
		}
		private void TokenDeleteButton_Click(object sender, EventArgs e)
		{
			if (MessageBox.Show("Accept to delete this token?", "Message", MessageBoxButtons.YesNo) == DialogResult.Yes)
			{
				TokenPreventDataSave = true;

				TokenList.Select();
				TokenDeleteFromXML(TokenList.GetItemText(TokenList.SelectedItem));

				int i = TokenList.SelectedIndex;
				++TokenListLastIndex;
				TokenList.Items.RemoveAt(TokenList.SelectedIndex);
				TokenList.SelectedIndex = (TokenList.Items.Count == i ? --i : i);
			}
		}

		private void TokenNameTextBox_TextChanged(object sender, EventArgs e)
		{
			if (TokenList.SelectedIndex == -1 || TokenNameTextBox.Text == "") return;
			TokenXML.Element(TokenList.GetItemText(TokenList.Items[TokenList.SelectedIndex])).Name = TokenNameTextBox.Text;
			TokenSaveXML();
			TokenList.Items[TokenList.SelectedIndex] = TokenNameTextBox.Text;
			TokenList.SelectedIndex = TokenListLastIndex;
		}

		private void TokenClassComboBox_SelectedIndexChanged(object sender, EventArgs e)
		{
			if (TokenPreventDataSave == true) return;
			TokenClassIndexLabel.Text = TokenClassComboBox.SelectedIndex.ToString();
			TokenXML.Element(TokenList.Text).Element(TokenClassLabel.Text).SetValue(TokenClassComboBox.SelectedIndex);
			TokenSaveXML();
		}

		private void TokenDMGNum1_ValueChanged(object sender, EventArgs e)
		{
			if (TokenPreventDataSave == true) return;
			TokenXML.Element(TokenList.Text).Element(TokenDMGLabel.Text).Element("Num1").SetValue(TokenDMGNum1.Value);
			TokenSaveXML();
		}
		private void TokenDMGNum2_ValueChanged(object sender, EventArgs e)
		{
			if (TokenPreventDataSave == true) return;
			TokenXML.Element(TokenList.Text).Element(TokenDMGLabel.Text).Element("Num2").SetValue(TokenDMGNum2.Value);
			TokenSaveXML();
		}
		private void TokenDMGTurnNum_ValueChanged(object sender, EventArgs e)
		{
			if (TokenPreventDataSave == true) return;
			TokenXML.Element(TokenList.Text).Element(TokenDMGLabel.Text).Element("Turn").SetValue(TokenDMGTurnNum.Value);
			TokenSaveXML();
		}
		private void TokenSTANum1_ValueChanged(object sender, EventArgs e)
		{
			if (TokenPreventDataSave == true) return;
			TokenXML.Element(TokenList.Text).Element(TokenSPLabel.Text).Element("Num1").SetValue(TokenSTANum1.Value);
			TokenSaveXML();
		}
		private void TokenSTANum2_ValueChanged(object sender, EventArgs e)
		{
			if (TokenPreventDataSave == true) return;
			TokenXML.Element(TokenList.Text).Element(TokenSPLabel.Text).Element("Num2").SetValue(TokenSTANum2.Value);
			TokenSaveXML();
		}
		private void TokenSTATurnNum_ValueChanged(object sender, EventArgs e)
		{
			if (TokenPreventDataSave == true) return;
			TokenXML.Element(TokenList.Text).Element(TokenSPLabel.Text).Element("Turn").SetValue(TokenSTATurnNum.Value);
			TokenSaveXML();
		}
		private void TokenSTA_ReNum1_ValueChanged(object sender, EventArgs e)
		{
			if (TokenPreventDataSave == true) return;
			TokenXML.Element(TokenList.Text).Element(TokenSP_ReLabel.Text).Element("Num1").SetValue(TokenSTA_ReNum1.Value);
			TokenSaveXML();
		}
		private void TokenSTA_ReNum2_ValueChanged(object sender, EventArgs e)
		{
			if (TokenPreventDataSave == true) return;
			TokenXML.Element(TokenList.Text).Element(TokenSP_ReLabel.Text).Element("Num2").SetValue(TokenSTA_ReNum2.Value);
			TokenSaveXML();
		}
		private void TokenSTA_ReTargetComboBox_SelectedIndexChanged(object sender, EventArgs e)
		{
			if (TokenPreventDataSave == true) return;
			TokenXML.Element(TokenList.Text).Element(TokenSP_ReLabel.Text).Element("Target").SetValue(TokenSTA_ReTargetComboBox.SelectedIndex);
			TokenSaveXML();
		}
		private void TokenSTA_ReTurnNum_ValueChanged(object sender, EventArgs e)
		{
			if (TokenPreventDataSave == true) return;
			TokenXML.Element(TokenList.Text).Element(TokenSP_ReLabel.Text).Element("Turn").SetValue(TokenSTA_ReTurnNum.Value);
			TokenSaveXML();
		}
		private void TokenDEFNum1_ValueChanged(object sender, EventArgs e)
		{
			if (TokenPreventDataSave == true) return;
			TokenXML.Element(TokenList.Text).Element(TokenDEFLabel.Text).Element("Num1").SetValue(TokenDEFNum1.Value);
			TokenSaveXML();
		}
		private void TokenDEFNum2_ValueChanged(object sender, EventArgs e)
		{
			if (TokenPreventDataSave == true) return;
			TokenXML.Element(TokenList.Text).Element(TokenDEFLabel.Text).Element("Num2").SetValue(TokenDEFNum2.Value);
			TokenSaveXML();
		}
		private void TokenDEFTargetComboBox_SelectedIndexChanged(object sender, EventArgs e)
		{
			if (TokenPreventDataSave == true) return;
			TokenXML.Element(TokenList.Text).Element(TokenDEFLabel.Text).Element("Target").SetValue(TokenDEFTargetComboBox.SelectedIndex);
			TokenSaveXML();
		}
		private void TokenDEFTurnNum_ValueChanged(object sender, EventArgs e)
		{
			if (TokenPreventDataSave == true) return;
			TokenXML.Element(TokenList.Text).Element(TokenDEFLabel.Text).Element("Turn").SetValue(TokenDEFTurnNum.Value);
			TokenSaveXML();
		}
		private void TokenHPNum1_ValueChanged(object sender, EventArgs e)
		{
			if (TokenPreventDataSave == true) return;
			TokenXML.Element(TokenList.Text).Element(TokenHPLabel.Text).Element("Num1").SetValue(TokenHPNum1.Value);
			TokenSaveXML();
		}
		private void TokenHPNum2_ValueChanged(object sender, EventArgs e)
		{
			if (TokenPreventDataSave == true) return;
			TokenXML.Element(TokenList.Text).Element(TokenHPLabel.Text).Element("Num2").SetValue(TokenHPNum2.Value);
			TokenSaveXML();
		}
		private void TokenHPTargetComboBox_SelectedIndexChanged(object sender, EventArgs e)
		{
			if (TokenPreventDataSave == true) return;
			TokenXML.Element(TokenList.Text).Element(TokenHPLabel.Text).Element("Target").SetValue(TokenHPTargetComboBox.SelectedIndex);
			TokenSaveXML();
		}
		private void TokenHPTurnNum_ValueChanged(object sender, EventArgs e)
		{
			if (TokenPreventDataSave == true) return;
			TokenXML.Element(TokenList.Text).Element(TokenHPLabel.Text).Element("Turn").SetValue(TokenHPTurnNum.Value);
			TokenSaveXML();
		}
		private void TokenMPNum1_ValueChanged(object sender, EventArgs e)
		{
			if (TokenPreventDataSave == true) return;
			TokenXML.Element(TokenList.Text).Element(TokenMPLabel.Text).Element("Num1").SetValue(TokenMPNum1.Value);
			TokenSaveXML();
		}
		private void TokenMPNum2_ValueChanged(object sender, EventArgs e)
		{
			if (TokenPreventDataSave == true) return;
			TokenXML.Element(TokenList.Text).Element(TokenMPLabel.Text).Element("Num2").SetValue(TokenMPNum2.Value);
			TokenSaveXML();
		}
		private void TokenMPTurnNum_ValueChanged(object sender, EventArgs e)
		{
			if (TokenPreventDataSave == true) return;
			TokenXML.Element(TokenList.Text).Element(TokenMPLabel.Text).Element("Turn").SetValue(TokenMPTurnNum.Value);
			TokenSaveXML();
		}
		private void TokenHPStealNum1_ValueChanged(object sender, EventArgs e)
		{
			if (TokenPreventDataSave == true) return;
			TokenXML.Element(TokenList.Text).Element(TokenHPStealLabel.Text).Element("Num1").SetValue(TokenHPStealNum1.Value);
			TokenSaveXML();
		}
		private void TokenHPStealNum2_ValueChanged(object sender, EventArgs e)
		{
			if (TokenPreventDataSave == true) return;
			TokenXML.Element(TokenList.Text).Element(TokenHPStealLabel.Text).Element("Num2").SetValue(TokenHPStealNum2.Value);
			TokenSaveXML();
		}
		private void TokenHPStealTargetComboBox_SelectedIndexChanged(object sender, EventArgs e)
		{
			if (TokenPreventDataSave == true) return;
			TokenXML.Element(TokenList.Text).Element(TokenHPStealLabel.Text).Element("Target").SetValue(TokenHPStealTargetComboBox.SelectedIndex);
			TokenSaveXML();
		}
		private void TokenHPStealTurnNum_ValueChanged(object sender, EventArgs e)
		{
			if (TokenPreventDataSave == true) return;
			TokenXML.Element(TokenList.Text).Element(TokenHPStealLabel.Text).Element("Turn").SetValue(TokenHPStealTurnNum.Value);
			TokenSaveXML();
		}
		private void TokenSpeedNum1_ValueChanged(object sender, EventArgs e)
		{
			if (TokenPreventDataSave == true) return;
			TokenXML.Element(TokenList.Text).Element(TokenSpeedLabel.Text).Element("Num1").SetValue(TokenSpeedNum1.Value);
			TokenSaveXML();
		}
		private void TokenSpeedNum2_ValueChanged(object sender, EventArgs e)
		{
			if (TokenPreventDataSave == true) return;
			TokenXML.Element(TokenList.Text).Element(TokenSpeedLabel.Text).Element("Num2").SetValue(TokenSpeedNum2.Value);
			TokenSaveXML();
		}
		private void TokenSpeedTargetComboBox_SelectedIndexChanged(object sender, EventArgs e)
		{
			if (TokenPreventDataSave == true) return;
			TokenXML.Element(TokenList.Text).Element(TokenSpeedLabel.Text).Element("Target").SetValue(TokenSpeedTargetComboBox.SelectedIndex);
			TokenSaveXML();
		}
		private void TokenSpeedTurnNum_ValueChanged(object sender, EventArgs e)
		{
			if (TokenPreventDataSave == true) return;
			TokenXML.Element(TokenList.Text).Element(TokenSpeedLabel.Text).Element("Turn").SetValue(TokenSpeedTurnNum.Value);
			TokenSaveXML();
		}
		private void TokenDMGBuffNum1_ValueChanged(object sender, EventArgs e)
		{
			if (TokenPreventDataSave == true) return;
			TokenXML.Element(TokenList.Text).Element(TokenDMGBuffLabel.Text).Element("Num1").SetValue(TokenDMGBuffNum1.Value);
			TokenSaveXML();
		}
		private void TokenDMGBuffNum2_ValueChanged(object sender, EventArgs e)
		{
			if (TokenPreventDataSave == true) return;
			TokenXML.Element(TokenList.Text).Element(TokenDMGBuffLabel.Text).Element("Num2").SetValue(TokenDMGBuffNum2.Value);
			TokenSaveXML();
		}
		private void TokenDMGBuffTargetComboBox_SelectedIndexChanged(object sender, EventArgs e)
		{
			if (TokenPreventDataSave == true) return;
			TokenXML.Element(TokenList.Text).Element(TokenDMGBuffLabel.Text).Element("Target").SetValue(TokenDMGBuffTargetComboBox.SelectedIndex);
			TokenSaveXML();
		}
		private void TokenDMGBuffTurnNum_ValueChanged(object sender, EventArgs e)
		{
			if (TokenPreventDataSave == true) return;
			TokenXML.Element(TokenList.Text).Element(TokenDMGBuffLabel.Text).Element("Turn").SetValue(TokenDMGTurnNum.Value);
			TokenSaveXML();
		}

		private void TokenBuffList_SelectedIndexChanged(object sender, EventArgs e)
		{
			if (TokenBuffList.SelectedIndex == -1)
			{
				TokenBuffEditButton.Enabled = false;
				TokenBuffDeleteButton.Enabled = false;
			}
			else
			{
				TokenBuffEditButton.Enabled = true;
				TokenBuffDeleteButton.Enabled = true;
			}
		}
		private void TokenDebuffList_SelectedIndexChanged(object sender, EventArgs e)
		{
			if (TokenDebuffList.SelectedIndex == -1)
			{
				TokenDebuffEditButton.Enabled = false;
				TokenDebuffDeleteButton.Enabled = false;
			}
			else
			{
				TokenDebuffEditButton.Enabled = true;
				TokenDebuffDeleteButton.Enabled = true;
			}
		}

		private void TokenBuffAddButton_Click(object sender, EventArgs e)
		{
			TokenPropertyDialog dialog = new TokenPropertyDialog(TokenPropertyDialog.Type.Buff, TokenBuffList);
			if (dialog.ShowDialog() == DialogResult.OK)
			{
				TokenBuffList.Select();
				TokenBuffList.Items.Add(dialog.ResultItem);
				TokenBuffList.SelectedIndex = TokenBuffList.Items.Count - 1;
				TokenXML.Element(TokenList.GetItemText(TokenList.SelectedItem)).Element(TokenBuffLabel.Text).Add(
					new XElement(dialog.ResultItem.text,
						new XElement("Num1", dialog.ResultItem.num1),
						new XElement("Num2", dialog.ResultItem.num2),
						new XElement("Target", (short)dialog.ResultItem.target),
						new XElement("Turn", dialog.ResultItem.turn)));
				TokenSaveXML();
			}
		}
		private void TokenBuffEditButton_Click(object sender, EventArgs e)
		{
			TokenPropertyItem item = (TokenPropertyItem)TokenBuffList.SelectedItem;
			TokenPropertyDialog dialog = new TokenPropertyDialog(TokenPropertyDialog.Type.Buff, item);
			if (dialog.ShowDialog() == DialogResult.OK)
			{
				TokenBuffList.Select();
				item.num1 = dialog.ResultItem.num1;
				item.num2 = dialog.ResultItem.num2;
				item.target = dialog.ResultItem.target;
				item.turn = dialog.ResultItem.turn;
				TokenXML.Element(TokenList.GetItemText(TokenList.SelectedItem)).Element(TokenBuffLabel.Text).Element(dialog.ResultItem.text).Element("Num1").SetValue(dialog.ResultItem.num1);
				TokenXML.Element(TokenList.GetItemText(TokenList.SelectedItem)).Element(TokenBuffLabel.Text).Element(dialog.ResultItem.text).Element("Num2").SetValue(dialog.ResultItem.num2);
				TokenXML.Element(TokenList.GetItemText(TokenList.SelectedItem)).Element(TokenBuffLabel.Text).Element(dialog.ResultItem.text).Element("Target").SetValue((short)dialog.ResultItem.target);
				TokenXML.Element(TokenList.GetItemText(TokenList.SelectedItem)).Element(TokenBuffLabel.Text).Element(dialog.ResultItem.text).Element("Turn").SetValue(dialog.ResultItem.turn);
				TokenSaveXML();
			}
		}
		private void TokenBuffDeleteButton_Click(object sender, EventArgs e)
		{
			if (MessageBox.Show("Accept to delete this item?", "Message", MessageBoxButtons.YesNo) == DialogResult.Yes)
			{
				TokenBuffList.Select();
				int i = TokenBuffList.SelectedIndex;
				TokenBuffList.Items.RemoveAt(TokenBuffList.SelectedIndex);
				TokenBuffList.SelectedIndex = (TokenBuffList.Items.Count == i ? --i : i);
			}
		}

		private void TokenDebuffAddButton_Click(object sender, EventArgs e)
		{
			TokenPropertyDialog dialog = new TokenPropertyDialog(TokenPropertyDialog.Type.Debuff, TokenDebuffList);
			if (dialog.ShowDialog() == DialogResult.OK)
			{
				TokenDebuffList.Select();
				TokenDebuffList.Items.Add(dialog.ResultItem);
				TokenDebuffList.SelectedIndex = TokenDebuffList.Items.Count - 1;
				TokenXML.Element(TokenList.GetItemText(TokenList.SelectedItem)).Element(TokenDebuffLabel.Text).Add(
					new XElement(dialog.ResultItem.text,
						new XElement("Num1", dialog.ResultItem.num1),
						new XElement("Num2", dialog.ResultItem.num2),
						new XElement("Target", (short)dialog.ResultItem.target),
						new XElement("Turn", dialog.ResultItem.turn)));
				TokenSaveXML();
			}
		}
		private void TokenDebuffEditButton_Click(object sender, EventArgs e)
		{
			TokenPropertyItem item = (TokenPropertyItem)TokenDebuffList.SelectedItem;
			TokenPropertyDialog dialog = new TokenPropertyDialog(TokenPropertyDialog.Type.Debuff, item);
			if (dialog.ShowDialog() == DialogResult.OK)
			{
				TokenDebuffList.Select();
				item.num1 = dialog.ResultItem.num1;
				item.num2 = dialog.ResultItem.num2;
				item.target = dialog.ResultItem.target;
				item.turn = dialog.ResultItem.turn;
				TokenXML.Element(TokenList.GetItemText(TokenList.SelectedItem)).Element(TokenDebuffLabel.Text).Element(dialog.ResultItem.text).Element("Num1").SetValue(dialog.ResultItem.num1);
				TokenXML.Element(TokenList.GetItemText(TokenList.SelectedItem)).Element(TokenDebuffLabel.Text).Element(dialog.ResultItem.text).Element("Num2").SetValue(dialog.ResultItem.num2);
				TokenXML.Element(TokenList.GetItemText(TokenList.SelectedItem)).Element(TokenDebuffLabel.Text).Element(dialog.ResultItem.text).Element("Target").SetValue((short)dialog.ResultItem.target);
				TokenXML.Element(TokenList.GetItemText(TokenList.SelectedItem)).Element(TokenDebuffLabel.Text).Element(dialog.ResultItem.text).Element("Turn").SetValue(dialog.ResultItem.turn);
				TokenSaveXML();
			}
		}
		private void TokenDebuffDeleteButton_Click(object sender, EventArgs e)
		{
			if (MessageBox.Show("Accept to delete this item?", "Message", MessageBoxButtons.YesNo) == DialogResult.Yes)
			{
				TokenDebuffList.Select();
				int i = TokenDebuffList.SelectedIndex;
				TokenDebuffList.Items.RemoveAt(TokenDebuffList.SelectedIndex);
				TokenDebuffList.SelectedIndex = (TokenDebuffList.Items.Count == i ? --i : i);
			}
		}

		#endregion Token Tab

		#region Armor Tab

		private int ArmorListLastIndex;
		private bool ArmorPreventDataSave = false;

		private void ArmorSaveXML()
		{
			ArmorXML.Save("Armors.xml");
		}
		private void ArmorComponentClear()
		{
			ArmorNameTextBox.Text = "";
			ArmorEnhanceNum.Value = 0;
			ArmorTypeComboBox.SelectedIndex = 0;

			ArmorHelmetDEFNum.Value = 0;
			ArmorHelmetDEFRateNum.Value = 0;
			ArmorHelmetDEFInitNum.Value = 0;
			ArmorHelmetHPInitNum.Value = 0;
			ArmorHelmetHPRateNum.Value = 0;
			ArmorHelmetHPNum.Value = 0;
			ArmorArmorDEFNum.Value = 0;
			ArmorArmorDEFRateNum.Value = 0;
			ArmorArmorDEFInitNum.Value = 0;
			ArmorArmorHPInitNum.Value = 0;
			ArmorArmorHPRateNum.Value = 0;
			ArmorArmorHPNum.Value = 0;
			ArmorGloveDEFNum.Value = 0;
			ArmorGloveDEFRateNum.Value = 0;
			ArmorGloveDEFInitNum.Value = 0;
			ArmorGloveHPInitNum.Value = 0;
			ArmorGloveHPRateNum.Value = 0;
			ArmorGloveHPNum.Value = 0;
			ArmorShoesDEFNum.Value = 0;
			ArmorShoesDEFRateNum.Value = 0;
			ArmorShoesDEFInitNum.Value = 0;
			ArmorShoesHPInitNum.Value = 0;
			ArmorShoesHPRateNum.Value = 0;
			ArmorShoesHPNum.Value = 0;

			ArmorSetOptionTextBox.Text = "";
		}
		private void ArmorComponentEnabled(bool b)
		{
			ArmorNameTextBox.Enabled = b;
			ArmorEnhanceNum.Enabled = b;
			ArmorTypeComboBox.Enabled = b;

			ArmorHelmetDEFNum.Enabled = b;
			ArmorHelmetDEFInitNum.Enabled = b;
			ArmorHelmetDEFRateNum.Enabled = b;
			ArmorHelmetHPNum.Enabled = b;
			ArmorHelmetHPInitNum.Enabled = b;
			ArmorHelmetHPRateNum.Enabled = b;
			ArmorArmorDEFNum.Enabled = b;
			ArmorArmorDEFInitNum.Enabled = b;
			ArmorArmorDEFRateNum.Enabled = b;
			ArmorArmorHPNum.Enabled = b;
			ArmorArmorHPInitNum.Enabled = b;
			ArmorArmorHPRateNum.Enabled = b;
			ArmorGloveDEFNum.Enabled = b;
			ArmorGloveDEFInitNum.Enabled = b;
			ArmorGloveDEFRateNum.Enabled = b;
			ArmorGloveHPNum.Enabled = b;
			ArmorGloveHPInitNum.Enabled = b;
			ArmorGloveHPRateNum.Enabled = b;
			ArmorShoesDEFNum.Enabled = b;
			ArmorShoesDEFInitNum.Enabled = b;
			ArmorShoesDEFRateNum.Enabled = b;
			ArmorShoesHPNum.Enabled = b;
			ArmorShoesHPInitNum.Enabled = b;
			ArmorShoesHPRateNum.Enabled = b;

			ArmorSetOptionTextBox.Enabled = b;
		}
		private void ArmorLoadXMLToComponent(string armor)
		{
			ArmorNameTextBox.Text = armor;
			ArmorEnhanceNum.Value = 0;
			ArmorTypeComboBox.SelectedIndex = Int32.Parse(ArmorXML.Element(armor).Element(ArmorTypeLabel.Text).Value);

			ArmorHelmetDEFInitNum.Value = Decimal.Parse(ArmorXML.Element(armor).Element(ArmorHelmetLabel.Text).Element(ArmorHelmetDEFLabel.Text).Element("Init").Value);
			ArmorHelmetDEFRateNum.Value = Decimal.Parse(ArmorXML.Element(armor).Element(ArmorHelmetLabel.Text).Element(ArmorHelmetDEFLabel.Text).Element("Rate").Value);
			ArmorHelmetDEFNum.Value = ArmorHelmetDEFInitNum.Value + ArmorEnhanceNum.Value * ArmorHelmetDEFRateNum.Value;
			ArmorHelmetHPInitNum.Value = Decimal.Parse(ArmorXML.Element(armor).Element(ArmorHelmetLabel.Text).Element(ArmorHelmetHPLabel.Text).Element("Init").Value);
			ArmorHelmetHPRateNum.Value = Decimal.Parse(ArmorXML.Element(armor).Element(ArmorHelmetLabel.Text).Element(ArmorHelmetHPLabel.Text).Element("Rate").Value);
			ArmorHelmetHPNum.Value = ArmorHelmetHPInitNum.Value + ArmorEnhanceNum.Value * ArmorHelmetHPRateNum.Value;
			ArmorArmorDEFInitNum.Value = Decimal.Parse(ArmorXML.Element(armor).Element(ArmorArmorLabel.Text).Element(ArmorArmorDEFLabel.Text).Element("Init").Value);
			ArmorArmorDEFRateNum.Value = Decimal.Parse(ArmorXML.Element(armor).Element(ArmorArmorLabel.Text).Element(ArmorArmorDEFLabel.Text).Element("Rate").Value);
			ArmorArmorDEFNum.Value = ArmorArmorDEFInitNum.Value + ArmorEnhanceNum.Value * ArmorArmorDEFRateNum.Value;
			ArmorArmorHPInitNum.Value = Decimal.Parse(ArmorXML.Element(armor).Element(ArmorArmorLabel.Text).Element(ArmorArmorHPLabel.Text).Element("Init").Value);
			ArmorArmorHPRateNum.Value = Decimal.Parse(ArmorXML.Element(armor).Element(ArmorArmorLabel.Text).Element(ArmorArmorHPLabel.Text).Element("Rate").Value);
			ArmorArmorHPNum.Value = ArmorArmorHPInitNum.Value + ArmorEnhanceNum.Value * ArmorArmorHPRateNum.Value;
			ArmorGloveDEFInitNum.Value = Decimal.Parse(ArmorXML.Element(armor).Element(ArmorGloveLabel.Text).Element(ArmorGloveDEFLabel.Text).Element("Init").Value);
			ArmorGloveDEFRateNum.Value = Decimal.Parse(ArmorXML.Element(armor).Element(ArmorGloveLabel.Text).Element(ArmorGloveDEFLabel.Text).Element("Rate").Value);
			ArmorGloveDEFNum.Value = ArmorGloveDEFInitNum.Value + ArmorEnhanceNum.Value * ArmorGloveDEFRateNum.Value;
			ArmorGloveHPInitNum.Value = Decimal.Parse(ArmorXML.Element(armor).Element(ArmorGloveLabel.Text).Element(ArmorGloveHPLabel.Text).Element("Init").Value);
			ArmorGloveHPRateNum.Value = Decimal.Parse(ArmorXML.Element(armor).Element(ArmorGloveLabel.Text).Element(ArmorGloveHPLabel.Text).Element("Rate").Value);
			ArmorGloveHPNum.Value = ArmorGloveHPInitNum.Value + ArmorEnhanceNum.Value * ArmorGloveHPRateNum.Value;
			ArmorShoesDEFInitNum.Value = Decimal.Parse(ArmorXML.Element(armor).Element(ArmorShoesLabel.Text).Element(ArmorShoesDEFLabel.Text).Element("Init").Value);
			ArmorShoesDEFRateNum.Value = Decimal.Parse(ArmorXML.Element(armor).Element(ArmorShoesLabel.Text).Element(ArmorShoesDEFLabel.Text).Element("Rate").Value);
			ArmorShoesDEFNum.Value = ArmorShoesDEFInitNum.Value + ArmorEnhanceNum.Value * ArmorShoesDEFRateNum.Value;
			ArmorShoesHPInitNum.Value = Decimal.Parse(ArmorXML.Element(armor).Element(ArmorShoesLabel.Text).Element(ArmorShoesHPLabel.Text).Element("Init").Value);
			ArmorShoesHPRateNum.Value = Decimal.Parse(ArmorXML.Element(armor).Element(ArmorShoesLabel.Text).Element(ArmorShoesHPLabel.Text).Element("Rate").Value);
			ArmorShoesHPNum.Value = ArmorShoesHPInitNum.Value + ArmorEnhanceNum.Value * ArmorShoesHPRateNum.Value;

			ArmorSetOptionTextBox.Text = ArmorXML.Element(armor).Element(ArmorSetOptionLabel.Text).Value;
		}

		private void ArmorAddToXML(string armor)
		{
			ArmorXML.Add(new XElement(armor,
				new XElement(ArmorTypeLabel.Text, ArmorTypeComboBox.SelectedIndex),
				new XElement(ArmorHelmetLabel.Text,
					new XElement(ArmorHelmetDEFLabel.Text,
						new XElement("Init", ArmorHelmetDEFInitNum.Value),
						new XElement("Rate", ArmorHelmetDEFRateNum.Value)),
					new XElement(ArmorHelmetHPLabel.Text,
						new XElement("Init", ArmorHelmetHPInitNum.Value),
						new XElement("Rate", ArmorHelmetHPRateNum.Value))),
				new XElement(ArmorArmorLabel.Text,
					new XElement(ArmorArmorDEFLabel.Text,
						new XElement("Init", ArmorArmorDEFInitNum.Value),
						new XElement("Rate", ArmorArmorDEFRateNum.Value)),
					new XElement(ArmorArmorHPLabel.Text,
						new XElement("Init", ArmorArmorHPInitNum.Value),
						new XElement("Rate", ArmorArmorHPRateNum.Value))),
				new XElement(ArmorGloveLabel.Text,
					new XElement(ArmorGloveDEFLabel.Text,
						new XElement("Init", ArmorGloveDEFInitNum.Value),
						new XElement("Rate", ArmorGloveDEFRateNum.Value)),
					new XElement(ArmorGloveHPLabel.Text,
						new XElement("Init", ArmorGloveHPInitNum.Value),
						new XElement("Rate", ArmorGloveHPRateNum.Value))),
				new XElement(ArmorShoesLabel.Text,
					new XElement(ArmorShoesDEFLabel.Text,
						new XElement("Init", ArmorShoesDEFInitNum.Value),
						new XElement("Rate", ArmorShoesDEFRateNum.Value)),
					new XElement(ArmorShoesHPLabel.Text,
						new XElement("Init", ArmorShoesHPInitNum.Value),
						new XElement("Rate", ArmorShoesHPRateNum.Value))),
				new XElement(ArmorSetOptionLabel.Text, ArmorSetOptionTextBox.Text)));
			ArmorSaveXML();
		}
		private void ArmorDeleteFromXML(string armor)
		{
			ArmorXML.Element(armor).Remove();
			ArmorSaveXML();
		}

		private void ArmorList_SelectedIndexChanged(object sender, EventArgs e)
		{
			if (ArmorList.SelectedIndex == ArmorListLastIndex)
			{
				return;
			}
			if (ArmorList.Items.Count == 0)
			{
				ArmorComponentEnabled(false);
				ArmorDeleteButton.Enabled = false;
				ArmorComponentClear();
				ArmorPreventDataSave = false;
				ArmorIndexLabel.Text = "-";
			}
			else
			{
				if (ArmorList.SelectedIndex != -1)
				{
					ArmorListLastIndex = ArmorList.SelectedIndex;
					ArmorLoadXMLToComponent(ArmorList.GetItemText(ArmorList.Items[ArmorListLastIndex]));
					ArmorComponentEnabled(true);
					ArmorDeleteButton.Enabled = true;
					ArmorPreventDataSave = false;
					ArmorIndexLabel.Text = ArmorListLastIndex.ToString();
				}
			}
		}

		private void ArmorAddButton_Click(object sender, EventArgs e)
		{
			NameInputDialog dialog = new NameInputDialog(ArmorXML);
			if (dialog.ShowDialog() == DialogResult.OK)
			{
				ArmorPreventDataSave = true;
				ArmorList.Select();
				ArmorComponentClear();
				ArmorAddToXML(dialog.ResultText);
				ArmorList.Items.Add(dialog.ResultText);
				ArmorList.SelectedIndex = ArmorList.Items.Count - 1;
				ArmorNameTextBox.Text = dialog.ResultText;
			}
		}
		private void ArmorDeleteButton_Click(object sender, EventArgs e)
		{
			if (MessageBox.Show("Accept to delete this armor?", "Message", MessageBoxButtons.YesNo) == DialogResult.Yes)
			{
				ArmorPreventDataSave = true;

				ArmorList.Select();
				ArmorDeleteFromXML(ArmorList.GetItemText(ArmorList.SelectedItem));

				int i = ArmorList.SelectedIndex;
				++ArmorListLastIndex;
				ArmorList.Items.RemoveAt(ArmorList.SelectedIndex);
				ArmorList.SelectedIndex = (ArmorList.Items.Count == i ? --i : i);
			}
		}

		private void ArmorNameTextBox_TextChanged(object sender, EventArgs e)
		{
			if (ArmorList.SelectedIndex == -1 || ArmorNameTextBox.Text == "") return;
			ArmorXML.Element(ArmorList.GetItemText(ArmorList.Items[ArmorList.SelectedIndex])).Name = ArmorNameTextBox.Text;
			ArmorSaveXML();
			ArmorList.Items[ArmorList.SelectedIndex] = ArmorNameTextBox.Text;
			ArmorList.SelectedIndex = ArmorListLastIndex;
		}
		private void ArmorEnhanceNum_ValueChanged(object sender, EventArgs e)
		{
			ArmorHelmetDEFNum.Value = ArmorHelmetDEFInitNum.Value + ArmorEnhanceNum.Value * ArmorHelmetDEFRateNum.Value;
			ArmorHelmetHPNum.Value = ArmorHelmetHPInitNum.Value + ArmorEnhanceNum.Value * ArmorHelmetHPRateNum.Value;
			ArmorArmorDEFNum.Value = ArmorArmorDEFInitNum.Value + ArmorEnhanceNum.Value * ArmorArmorDEFRateNum.Value;
			ArmorArmorHPNum.Value = ArmorArmorHPInitNum.Value + ArmorEnhanceNum.Value * ArmorArmorHPRateNum.Value;
			ArmorGloveDEFNum.Value = ArmorGloveDEFInitNum.Value + ArmorEnhanceNum.Value * ArmorGloveDEFRateNum.Value;
			ArmorGloveHPNum.Value = ArmorGloveHPInitNum.Value + ArmorEnhanceNum.Value * ArmorGloveHPRateNum.Value;
			ArmorShoesDEFNum.Value = ArmorShoesDEFInitNum.Value + ArmorEnhanceNum.Value * ArmorShoesDEFRateNum.Value;
			ArmorShoesHPNum.Value = ArmorShoesHPInitNum.Value + ArmorEnhanceNum.Value * ArmorShoesHPRateNum.Value;
		}
		private void ArmorTypeComboBox_SelectedIndexChanged(object sender, EventArgs e)
		{
			if (ArmorPreventDataSave == true) return;
			ArmorXML.Element(ArmorList.Text).Element(ArmorTypeLabel.Text).SetValue(ArmorTypeComboBox.SelectedIndex);
			ArmorSaveXML();
		}

		private void ArmorHelmetDEFInitNum_ValueChanged(object sender, EventArgs e)
		{
			ArmorHelmetDEFNum.Value = ArmorHelmetDEFInitNum.Value + ArmorEnhanceNum.Value * ArmorHelmetDEFRateNum.Value;
			if (ArmorPreventDataSave == true) return;
			ArmorXML.Element(ArmorList.Text).Element(ArmorHelmetLabel.Text).Element(ArmorHelmetDEFLabel.Text).Element("Init").SetValue(ArmorHelmetDEFInitNum.Value);
			ArmorSaveXML();
		}
		private void ArmorHelmetDEFRateNum_ValueChanged(object sender, EventArgs e)
		{
			ArmorHelmetDEFNum.Value = ArmorHelmetDEFInitNum.Value + ArmorEnhanceNum.Value * ArmorHelmetDEFRateNum.Value;
			if (ArmorPreventDataSave == true) return;
			ArmorXML.Element(ArmorList.Text).Element(ArmorHelmetLabel.Text).Element(ArmorHelmetDEFLabel.Text).Element("Rate").SetValue(ArmorHelmetDEFRateNum.Value);
			ArmorSaveXML();
		}
		private void ArmorHelmetHPInitNum_ValueChanged(object sender, EventArgs e)
		{
			ArmorHelmetHPNum.Value = ArmorHelmetHPInitNum.Value + ArmorEnhanceNum.Value * ArmorHelmetHPRateNum.Value;
			if (ArmorPreventDataSave == true) return;
			ArmorXML.Element(ArmorList.Text).Element(ArmorHelmetLabel.Text).Element(ArmorHelmetHPLabel.Text).Element("Init").SetValue(ArmorHelmetHPInitNum.Value);
			ArmorSaveXML();
		}
		private void ArmorHelmetHPRateNum_ValueChanged(object sender, EventArgs e)
		{
			ArmorHelmetHPNum.Value = ArmorHelmetHPInitNum.Value + ArmorEnhanceNum.Value * ArmorHelmetHPRateNum.Value;
			if (ArmorPreventDataSave == true) return;
			ArmorXML.Element(ArmorList.Text).Element(ArmorHelmetLabel.Text).Element(ArmorHelmetHPLabel.Text).Element("Rate").SetValue(ArmorHelmetHPRateNum.Value);
			ArmorSaveXML();
		}
		private void ArmorArmorDEFInitNum_ValueChanged(object sender, EventArgs e)
		{
			ArmorArmorDEFNum.Value = ArmorArmorDEFInitNum.Value + ArmorEnhanceNum.Value * ArmorArmorDEFRateNum.Value;
			if (ArmorPreventDataSave == true) return;
			ArmorXML.Element(ArmorList.Text).Element(ArmorArmorLabel.Text).Element(ArmorArmorDEFLabel.Text).Element("Init").SetValue(ArmorArmorDEFInitNum.Value);
			ArmorSaveXML();
		}
		private void ArmorArmorDEFRateNum_ValueChanged(object sender, EventArgs e)
		{
			ArmorArmorDEFNum.Value = ArmorArmorDEFInitNum.Value + ArmorEnhanceNum.Value * ArmorArmorDEFRateNum.Value;
			if (ArmorPreventDataSave == true) return;
			ArmorXML.Element(ArmorList.Text).Element(ArmorArmorLabel.Text).Element(ArmorArmorDEFLabel.Text).Element("Rate").SetValue(ArmorArmorDEFRateNum.Value);
			ArmorSaveXML();
		}
		private void ArmorArmorHPInitNum_ValueChanged(object sender, EventArgs e)
		{
			ArmorArmorHPNum.Value = ArmorArmorHPInitNum.Value + ArmorEnhanceNum.Value * ArmorArmorHPRateNum.Value;
			if (ArmorPreventDataSave == true) return;
			ArmorXML.Element(ArmorList.Text).Element(ArmorArmorLabel.Text).Element(ArmorArmorHPLabel.Text).Element("Init").SetValue(ArmorArmorHPInitNum.Value);
			ArmorSaveXML();
		}
		private void ArmorArmorHPRateNum_ValueChanged(object sender, EventArgs e)
		{
			ArmorArmorHPNum.Value = ArmorArmorHPInitNum.Value + ArmorEnhanceNum.Value * ArmorArmorHPRateNum.Value;
			if (ArmorPreventDataSave == true) return;
			ArmorXML.Element(ArmorList.Text).Element(ArmorArmorLabel.Text).Element(ArmorArmorHPLabel.Text).Element("Rate").SetValue(ArmorArmorHPRateNum.Value);
			ArmorSaveXML();
		}
		private void ArmorGloveDEFInitNum_ValueChanged(object sender, EventArgs e)
		{
			ArmorGloveDEFNum.Value = ArmorGloveDEFInitNum.Value + ArmorEnhanceNum.Value * ArmorGloveDEFRateNum.Value;
			if (ArmorPreventDataSave == true) return;
			ArmorXML.Element(ArmorList.Text).Element(ArmorGloveLabel.Text).Element(ArmorGloveDEFLabel.Text).Element("Init").SetValue(ArmorGloveDEFInitNum.Value);
			ArmorSaveXML();
		}
		private void ArmorGloveDEFRateNum_ValueChanged(object sender, EventArgs e)
		{
			ArmorGloveDEFNum.Value = ArmorGloveDEFInitNum.Value + ArmorEnhanceNum.Value * ArmorGloveDEFRateNum.Value;
			if (ArmorPreventDataSave == true) return;
			ArmorXML.Element(ArmorList.Text).Element(ArmorGloveLabel.Text).Element(ArmorGloveDEFLabel.Text).Element("Rate").SetValue(ArmorGloveDEFRateNum.Value);
			ArmorSaveXML();
		}
		private void ArmorGloveHPInitNum_ValueChanged(object sender, EventArgs e)
		{
			ArmorGloveHPNum.Value = ArmorGloveHPInitNum.Value + ArmorEnhanceNum.Value * ArmorGloveHPRateNum.Value;
			if (ArmorPreventDataSave == true) return;
			ArmorXML.Element(ArmorList.Text).Element(ArmorGloveLabel.Text).Element(ArmorGloveHPLabel.Text).Element("Init").SetValue(ArmorGloveHPInitNum.Value);
			ArmorSaveXML();
		}
		private void ArmorGloveHPRateNum_ValueChanged(object sender, EventArgs e)
		{
			ArmorGloveHPNum.Value = ArmorGloveHPInitNum.Value + ArmorEnhanceNum.Value * ArmorGloveHPRateNum.Value;
			if (ArmorPreventDataSave == true) return;
			ArmorXML.Element(ArmorList.Text).Element(ArmorGloveLabel.Text).Element(ArmorGloveHPLabel.Text).Element("Rate").SetValue(ArmorGloveHPRateNum.Value);
			ArmorSaveXML();
		}
		private void ArmorShoesDEFInitNum_ValueChanged(object sender, EventArgs e)
		{
			ArmorShoesDEFNum.Value = ArmorShoesDEFInitNum.Value + ArmorEnhanceNum.Value * ArmorShoesDEFRateNum.Value;
			if (ArmorPreventDataSave == true) return;
			ArmorXML.Element(ArmorList.Text).Element(ArmorShoesLabel.Text).Element(ArmorShoesDEFLabel.Text).Element("Init").SetValue(ArmorShoesDEFInitNum.Value);
			ArmorSaveXML();
		}
		private void ArmorShoesDEFRateNum_ValueChanged(object sender, EventArgs e)
		{
			ArmorShoesDEFNum.Value = ArmorShoesDEFInitNum.Value + ArmorEnhanceNum.Value * ArmorShoesDEFRateNum.Value;
			if (ArmorPreventDataSave == true) return;
			ArmorXML.Element(ArmorList.Text).Element(ArmorShoesLabel.Text).Element(ArmorShoesDEFLabel.Text).Element("Rate").SetValue(ArmorShoesDEFRateNum.Value);
			ArmorSaveXML();
		}
		private void ArmorShoesHPInitNum_ValueChanged(object sender, EventArgs e)
		{
			ArmorShoesHPNum.Value = ArmorShoesHPInitNum.Value + ArmorEnhanceNum.Value * ArmorShoesHPRateNum.Value;
			if (ArmorPreventDataSave == true) return;
			ArmorXML.Element(ArmorList.Text).Element(ArmorShoesLabel.Text).Element(ArmorShoesHPLabel.Text).Element("Init").SetValue(ArmorShoesHPInitNum.Value);
			ArmorSaveXML();
		}
		private void ArmorShoesHPRateNum_ValueChanged(object sender, EventArgs e)
		{
			ArmorShoesHPNum.Value = ArmorShoesHPInitNum.Value + ArmorEnhanceNum.Value * ArmorShoesHPRateNum.Value;
			if (ArmorPreventDataSave == true) return;
			ArmorXML.Element(ArmorList.Text).Element(ArmorShoesLabel.Text).Element(ArmorShoesHPLabel.Text).Element("Rate").SetValue(ArmorShoesHPRateNum.Value);
			ArmorSaveXML();
		}

		private void ArmorSetOptionTextBox_TextChanged(object sender, EventArgs e)
		{
			if (ArmorPreventDataSave == true) return;
			ArmorXML.Element(ArmorList.Text).Element(ArmorSetOptionLabel.Text).SetValue(ArmorSetOptionTextBox.Text);
			ArmorSaveXML();
		}

		#endregion Armor Tab

		#region Weapon Tab

		private int WeaponListLastIndex;
		private bool WeaponPreventDataSave = false;

		private void WeaponSaveXML()
		{
			WeaponXML.Save("Weapons.xml");
		}
		private void WeaponComponentClear()
		{
			WeaponNameTextBox.Text = "";
			WeaponEnhanceNum.Value = 0;
			WeaponTypeComboBox.SelectedIndex = 0;

			WeaponDMGNum.Value = 0;
			WeaponDMGRateNum.Value = 0;
			WeaponDMGInitNum.Value = 0;
			WeaponOptionTextBox.Text = "";
		}
		private void WeaponComponentEnabled(bool b)
		{
			WeaponNameTextBox.Enabled = b;
			WeaponEnhanceNum.Enabled = b;
			WeaponTypeComboBox.Enabled = b;

			WeaponDMGNum.Enabled = b;
			WeaponDMGInitNum.Enabled = b;
			WeaponDMGRateNum.Enabled = b;
			WeaponOptionTextBox.Enabled = b;
		}
		private void WeaponLoadXMLToComponent(string weapon)
		{
			WeaponNameTextBox.Text = weapon;
			WeaponEnhanceNum.Value = 0;
			WeaponTypeComboBox.SelectedIndex = Int32.Parse(WeaponXML.Element(weapon).Element(WeaponTypeLabel.Text).Value);

			WeaponDMGInitNum.Value = Decimal.Parse(WeaponXML.Element(weapon).Element(WeaponDMGLabel.Text).Element("Init").Value);
			WeaponDMGRateNum.Value = Decimal.Parse(WeaponXML.Element(weapon).Element(WeaponDMGLabel.Text).Element("Rate").Value);
			WeaponDMGNum.Value = WeaponDMGInitNum.Value + WeaponEnhanceNum.Value * WeaponDMGRateNum.Value;
			WeaponOptionTextBox.Text = WeaponXML.Element(weapon).Element(WeaponOptionLabel.Text).Value;
		}

		private void WeaponAddToXML(string weapon)
		{
			WeaponXML.Add(new XElement(weapon,
				new XElement(WeaponTypeLabel.Text, WeaponTypeComboBox.SelectedIndex),
				new XElement(WeaponDMGLabel.Text,
					new XElement("Init", WeaponDMGInitNum.Value),
					new XElement("Rate", WeaponDMGRateNum.Value)),
				new XElement(WeaponOptionLabel.Text, WeaponOptionTextBox.Text)));
			WeaponSaveXML();
		}
		private void WeaponDeleteFromXML(string weapon)
		{
			WeaponXML.Element(weapon).Remove();
			WeaponSaveXML();
		}

		private void WeaponList_SelectedIndexChanged(object sender, EventArgs e)
		{
			if (WeaponList.SelectedIndex == WeaponListLastIndex)
			{
				return;
			}
			if (WeaponList.Items.Count == 0)
			{
				WeaponComponentEnabled(false);
				WeaponDeleteButton.Enabled = false;
				WeaponComponentClear();
				WeaponPreventDataSave = false;
				WeaponIndexLabel.Text = "-";
			}
			else
			{
				if (WeaponList.SelectedIndex != -1)
				{
					WeaponListLastIndex = WeaponList.SelectedIndex;
					WeaponLoadXMLToComponent(WeaponList.GetItemText(WeaponList.Items[WeaponListLastIndex]));
					WeaponComponentEnabled(true);
					WeaponDeleteButton.Enabled = true;
					WeaponPreventDataSave = false;
					WeaponIndexLabel.Text = WeaponListLastIndex.ToString();
				}
			}
		}

		private void WeaponAddButton_Click(object sender, EventArgs e)
		{
			NameInputDialog dialog = new NameInputDialog(WeaponXML);
			if (dialog.ShowDialog() == DialogResult.OK)
			{
				WeaponPreventDataSave = true;
				WeaponList.Select();
				WeaponComponentClear();
				WeaponAddToXML(dialog.ResultText);
				WeaponList.Items.Add(dialog.ResultText);
				WeaponList.SelectedIndex = WeaponList.Items.Count - 1;
				WeaponNameTextBox.Text = dialog.ResultText;
			}
		}
		private void WeaponDeleteButton_Click(object sender, EventArgs e)
		{
			if (MessageBox.Show("Accept to delete this weapon?", "Message", MessageBoxButtons.YesNo) == DialogResult.Yes)
			{
				WeaponPreventDataSave = true;

				WeaponList.Select();
				WeaponDeleteFromXML(WeaponList.GetItemText(WeaponList.SelectedItem));

				int i = WeaponList.SelectedIndex;
				++WeaponListLastIndex;
				WeaponList.Items.RemoveAt(WeaponList.SelectedIndex);
				WeaponList.SelectedIndex = (WeaponList.Items.Count == i ? --i : i);
			}
		}

		private void WeaponNameTextBox_TextChanged(object sender, EventArgs e)
		{
			if (WeaponList.SelectedIndex == -1 || WeaponNameTextBox.Text == "") return;
			WeaponXML.Element(WeaponList.GetItemText(WeaponList.Items[WeaponList.SelectedIndex])).Name = WeaponNameTextBox.Text;
			WeaponSaveXML();
			WeaponList.Items[WeaponList.SelectedIndex] = WeaponNameTextBox.Text;
			WeaponList.SelectedIndex = WeaponListLastIndex;
		}
		private void WeaponEnhanceNum_ValueChanged(object sender, EventArgs e)
		{
			WeaponDMGNum.Value = WeaponDMGInitNum.Value + WeaponEnhanceNum.Value * WeaponDMGRateNum.Value;
		}
		private void WeaponTypeComboBox_SelectedIndexChanged(object sender, EventArgs e)
		{
			if (WeaponPreventDataSave == true) return;
			WeaponXML.Element(WeaponList.Text).Element(WeaponTypeLabel.Text).SetValue(WeaponTypeComboBox.SelectedIndex);
			WeaponSaveXML();
		}

		private void WeaponDMGInitNum_ValueChanged(object sender, EventArgs e)
		{
			WeaponDMGNum.Value = WeaponDMGInitNum.Value + WeaponEnhanceNum.Value * WeaponDMGRateNum.Value;
			if (WeaponPreventDataSave == true) return;
			WeaponXML.Element(WeaponList.Text).Element(WeaponDMGLabel.Text).Element("Init").SetValue(WeaponDMGInitNum.Value);
			WeaponSaveXML();
		}
		private void WeaponDMGRateNum_ValueChanged(object sender, EventArgs e)
		{
			WeaponDMGNum.Value = WeaponDMGInitNum.Value + WeaponEnhanceNum.Value * WeaponDMGRateNum.Value;
			if (WeaponPreventDataSave == true) return;
			WeaponXML.Element(WeaponList.Text).Element(WeaponDMGLabel.Text).Element("Rate").SetValue(WeaponDMGRateNum.Value);
			WeaponSaveXML();
		}
		private void WeaponOptionTextBox_TextChanged(object sender, EventArgs e)
		{
			if (WeaponPreventDataSave == true) return;
			WeaponXML.Element(WeaponList.Text).Element(WeaponOptionLabel.Text).SetValue(WeaponOptionTextBox.Text);
			WeaponSaveXML();
		}

		#endregion Weapon Tab

		#region Perk Tab

		private int PerkListLastIndex;
		private bool PerkPreventDataSave = false;

		private void PerkSaveXML()
		{
			PerkXML.Save("Perks.xml");
		}
		private void PerkComponentClear()
		{
			PerkNameTextBox.Text = "";
			PerkClassComboBox.SelectedIndex = 0;
			PerkEffectTextBox.Text = "";
		}
		private void PerkComponentEnabled(bool b)
		{
			PerkNameTextBox.Enabled = b;
			PerkClassComboBox.Enabled = b;
			PerkEffectTextBox.Enabled = b;
		}
		private void PerkLoadXMLToComponent(string perk)
		{
			PerkNameTextBox.Text = perk;
			PerkClassComboBox.SelectedIndex = Int32.Parse(PerkXML.Element(perk).Element(PerkClassLabel.Text).Value);
			PerkEffectTextBox.Text = PerkXML.Element(perk).Element(PerkEffectLabel.Text).Value;
		}

		private void PerkAddToXML(string perk)
		{
			PerkXML.Add(new XElement(perk,
				new XElement(PerkClassLabel.Text, PerkClassComboBox.SelectedIndex),
				new XElement(PerkEffectLabel.Text, PerkEffectTextBox.Text)));
			PerkSaveXML();
		}
		private void PerkDeleteFromXML(string perk)
		{
			PerkXML.Element(perk).Remove();
			PerkSaveXML();
		}

		private void PerkList_SelectedIndexChanged(object sender, EventArgs e)
		{
			if (PerkList.SelectedIndex == PerkListLastIndex)
			{
				return;
			}
			if (PerkList.Items.Count == 0)
			{
				PerkComponentEnabled(false);
				PerkDeleteButton.Enabled = false;
				PerkComponentClear();
				PerkPreventDataSave = false;
				PerkIndexLabel.Text = "-";
			}
			else
			{
				if (PerkList.SelectedIndex != -1)
				{
					PerkListLastIndex = PerkList.SelectedIndex;
					PerkLoadXMLToComponent(PerkList.GetItemText(PerkList.Items[PerkListLastIndex]));
					PerkComponentEnabled(true);
					PerkDeleteButton.Enabled = true;
					PerkPreventDataSave = false;
					PerkIndexLabel.Text = PerkListLastIndex.ToString();
				}
			}
		}

		private void PerkAddButton_Click(object sender, EventArgs e)
		{
			NameInputDialog dialog = new NameInputDialog(PerkXML);
			if (dialog.ShowDialog() == DialogResult.OK)
			{
				PerkPreventDataSave = true;
				PerkList.Select();
				PerkComponentClear();
				PerkAddToXML(dialog.ResultText);
				PerkList.Items.Add(dialog.ResultText);
				PerkList.SelectedIndex = PerkList.Items.Count - 1;
				PerkNameTextBox.Text = dialog.ResultText;
			}
		}
		private void PerkDeleteButton_Click(object sender, EventArgs e)
		{
			if (MessageBox.Show("Accept to delete this perk?", "Message", MessageBoxButtons.YesNo) == DialogResult.Yes)
			{
				PerkPreventDataSave = true;

				PerkList.Select();
				PerkDeleteFromXML(PerkList.GetItemText(PerkList.SelectedItem));

				int i = PerkList.SelectedIndex;
				++PerkListLastIndex;
				PerkList.Items.RemoveAt(PerkList.SelectedIndex);
				PerkList.SelectedIndex = (PerkList.Items.Count == i ? --i : i);
			}
		}

		private void PerkNameTextBox_TextChanged(object sender, EventArgs e)
		{
			if (PerkList.SelectedIndex == -1 || PerkNameTextBox.Text == "") return;
			PerkXML.Element(PerkList.GetItemText(PerkList.Items[PerkList.SelectedIndex])).Name = PerkNameTextBox.Text;
			PerkSaveXML();
			PerkList.Items[PerkList.SelectedIndex] = PerkNameTextBox.Text;
			PerkList.SelectedIndex = PerkListLastIndex;
		}
		private void PerkClassComboBox_SelectedIndexChanged(object sender, EventArgs e)
		{
			if (PerkPreventDataSave == true) return;
			PerkXML.Element(PerkList.Text).Element(PerkClassLabel.Text).SetValue(PerkClassComboBox.SelectedIndex);
			PerkSaveXML();
		}
		private void PerkEffectTextBox_TextChanged(object sender, EventArgs e)
		{
			if (PerkPreventDataSave == true) return;
			PerkXML.Element(PerkList.Text).Element(PerkEffectLabel.Text).SetValue(PerkEffectTextBox.Text);
			PerkSaveXML();
		}

		#endregion Perk Tab

		#region Item Tab

		private int ItemListLastIndex;
		private bool ItemPreventDataSave = false;

		private void ItemSaveXML()
		{
			ItemXML.Save("Items.xml");
		}
		private void ItemComponentClear()
		{
			ItemNameTextBox.Text = "";
			ItemTypeComboBox.SelectedIndex = 0;
			ItemInfoTextBox.Text = "";
		}
		private void ItemComponentEnabled(bool b)
		{
			ItemNameTextBox.Enabled = b;
			ItemTypeComboBox.Enabled = b;
			ItemInfoTextBox.Enabled = b;
		}
		private void ItemLoadXMLToComponent(string item)
		{
			ItemNameTextBox.Text = item;
			ItemTypeComboBox.SelectedIndex = Int32.Parse(ItemXML.Element(item).Element(ItemTypeLabel.Text).Value);
			ItemInfoTextBox.Text = ItemXML.Element(item).Element(ItemInfoLabel.Text).Value;
		}

		private void ItemAddToXML(string item)
		{
			ItemXML.Add(new XElement(item,
				new XElement(ItemTypeLabel.Text, ItemTypeComboBox.SelectedIndex),
				new XElement(ItemInfoLabel.Text, ItemInfoTextBox.Text)));
			ItemSaveXML();
		}
		private void ItemDeleteFromXML(string item)
		{
			ItemXML.Element(item).Remove();
			ItemSaveXML();
		}

		private void ItemList_SelectedIndexChanged(object sender, EventArgs e)
		{
			if (ItemList.SelectedIndex == ItemListLastIndex)
			{
				return;
			}
			if (ItemList.Items.Count == 0)
			{
				ItemComponentEnabled(false);
				ItemDeleteButton.Enabled = false;
				ItemComponentClear();
				ItemPreventDataSave = false;
				ItemIndexLabel.Text = "-";
			}
			else
			{
				if (ItemList.SelectedIndex != -1)
				{
					ItemListLastIndex = ItemList.SelectedIndex;
					ItemLoadXMLToComponent(ItemList.GetItemText(ItemList.Items[ItemListLastIndex]));
					ItemComponentEnabled(true);
					ItemDeleteButton.Enabled = true;
					ItemPreventDataSave = false;
					ItemIndexLabel.Text = ItemListLastIndex.ToString();
				}
			}
		}

		private void ItemAddButton_Click(object sender, EventArgs e)
		{
			NameInputDialog dialog = new NameInputDialog(ItemXML);
			if (dialog.ShowDialog() == DialogResult.OK)
			{
				ItemPreventDataSave = true;
				ItemList.Select();
				ItemComponentClear();
				ItemAddToXML(dialog.ResultText);
				ItemList.Items.Add(dialog.ResultText);
				ItemList.SelectedIndex = ItemList.Items.Count - 1;
				ItemNameTextBox.Text = dialog.ResultText;
			}
		}
		private void ItemDeleteButton_Click(object sender, EventArgs e)
		{
			if (MessageBox.Show("Accept to delete this item?", "Message", MessageBoxButtons.YesNo) == DialogResult.Yes)
			{
				ItemPreventDataSave = true;

				ItemList.Select();
				ItemDeleteFromXML(ItemList.GetItemText(ItemList.SelectedItem));

				int i = ItemList.SelectedIndex;
				++ItemListLastIndex;
				ItemList.Items.RemoveAt(ItemList.SelectedIndex);
				ItemList.SelectedIndex = (ItemList.Items.Count == i ? --i : i);
			}
		}

		private void ItemNameTextBox_TextChanged(object sender, EventArgs e)
		{
			if (ItemList.SelectedIndex == -1 || ItemNameTextBox.Text == "") return;
			ItemXML.Element(ItemList.GetItemText(ItemList.Items[ItemList.SelectedIndex])).Name = ItemNameTextBox.Text;
			ItemSaveXML();
			ItemList.Items[ItemList.SelectedIndex] = ItemNameTextBox.Text;
			ItemList.SelectedIndex = ItemListLastIndex;
		}
		private void ItemTypeComboBox_SelectedIndexChanged(object sender, EventArgs e)
		{
			if (ItemPreventDataSave == true) return;
			ItemXML.Element(ItemList.Text).Element(ItemTypeLabel.Text).SetValue(ItemTypeComboBox.SelectedIndex);
			ItemSaveXML();
		}
		private void ItemInfoTextBox_TextChanged(object sender, EventArgs e)
		{
			if (ItemPreventDataSave == true) return;
			ItemXML.Element(ItemList.Text).Element(ItemInfoLabel.Text).SetValue(ItemInfoTextBox.Text);
			ItemSaveXML();
		}

		#endregion Item Tab
	}

	public enum TokenTarget : int
	{
		Self,
		All
	}

	public class TokenPropertyItem
	{
		public string text;
		public short num1;
		public short num2;
		public TokenTarget target;
		public ushort turn;

		public override string ToString()
		{
			return text;
		}
	}
}
