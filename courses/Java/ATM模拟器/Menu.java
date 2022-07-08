package atm;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import atm.MyExceptions.*;

public class Menu {
	private JFrame frame;
	private JPanel screen;
	private JPanel left, right;
	private JLabel welcome, notice, imageIcon;
	private JButton inqury, withdraw, deposit, login, changePassword, exit;

	public Menu() {
		frame = new JFrame("ATM柜员机模拟程序");
		frame.setSize(650, 400);
		frame.setLocationRelativeTo(null);
		frame.setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
		frame.setLayout(null);
		this.initMiddle(screen);
		this.initLeftPanel();
		this.initRightPanel();
		frame.setVisible(true);
	}

	private void initMiddle(JPanel panel) {
		welcome = new JLabel("欢迎使用ATM模拟程序");
		welcome.setSize(350, 40);
		welcome.setLocation(210, 7);
		welcome.setFont(new Font("宋体", Font.BOLD, 20));
		frame.add(welcome);

		notice = new JLabel("温馨提醒：子页面返回菜单页面请按“返回”按钮");
		notice.setSize(430, 40);
		notice.setLocation(130, 50);
		notice.setFont(new Font("宋体", Font.BOLD, 16));
		frame.add(notice);

		screen = new JPanel();
		screen.setSize(350, 270);
		screen.setLocation(140, 85);

		imageIcon = new JLabel(new ImageIcon("atm/src/HDU.jpg"));
		imageIcon.setBounds(0, 0, screen.getWidth(), screen.getHeight());
		screen.add(imageIcon);

		frame.add(screen);
	}

	private void initLeftPanel() {
		left = new JPanel();
		left.setSize(150, 450);
		left.setLocation(0, 0);
		left.setLayout(null);

		inqury = new JButton("查询");
		inqury.setSize(100, 40);
		inqury.setLocation(15, 130);
		inqury.setFont(new Font("宋体", Font.BOLD, 16));
		inqury.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				try {
					@SuppressWarnings("unused")
					Inqury inquryGui = new Inqury();
				} catch (CardIDException e1) {
					JOptionPane.showMessageDialog(frame, e1.getMessage());
				} catch (Exception e1) {
					e1.printStackTrace();
				}
			}
		});
		left.add(inqury);

		deposit = new JButton("存款");
		deposit.setSize(100, 40);
		deposit.setLocation(15, 185);
		deposit.setFont(new Font("宋体", Font.BOLD, 16));
		deposit.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				try {
					@SuppressWarnings("unused")
					Deposit depositGui = new Deposit();
				} catch (CardIDException e1) {
					JOptionPane.showMessageDialog(frame, e1.getMessage());
				} catch (Exception e1) {
					e1.printStackTrace();
				}
			}
		});
		left.add(deposit);

		withdraw = new JButton("取款");
		withdraw.setSize(100, 40);
		withdraw.setLocation(15, 240);
		withdraw.setFont(new Font("宋体", Font.BOLD, 16));
		withdraw.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				try {
					@SuppressWarnings("unused")
					Withdraw withdrawGui = new Withdraw();
				} catch (CardIDException e1) {
					JOptionPane.showMessageDialog(frame, e1.getMessage());
				} catch (Exception e1) {
					e1.printStackTrace();
				}
			}
		});
		left.add(withdraw);

		frame.add(left);
	}

	private void initRightPanel() {
		right = new JPanel();
		right.setSize(150, 450);
		right.setLocation(500, 0);
		right.setLayout(null);

		login = new JButton("登录");
		login.setSize(100, 40);
		login.setLocation(15, 130);
		login.setFont(new Font("宋体", Font.BOLD, 16));
		login.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				try {
					@SuppressWarnings("unused")
					LoginGui loginGui = new LoginGui();
				} catch (CardIDException e1) {
					JOptionPane.showMessageDialog(frame, e1.getMessage());
				} catch (Exception e1) {
					e1.printStackTrace();
				}
			}
		});
		right.add(login);

		changePassword = new JButton("改密");
		changePassword.setSize(100, 40);
		changePassword.setLocation(15, 185);
		changePassword.setFont(new Font("宋体", Font.BOLD, 16));
		changePassword.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				try {
					@SuppressWarnings("unused")
					ChangePassword changePasswordGui = new ChangePassword();
				} catch (CardIDException e1) {
					JOptionPane.showMessageDialog(frame, e1.getMessage());
				} catch (Exception e1) {
					e1.printStackTrace();
				}
			}
		});
		right.add(changePassword);

		exit = new JButton("退卡");
		exit.setSize(100, 40);
		exit.setLocation(15, 240);
		exit.setFont(new Font("宋体", Font.BOLD, 16));
		exit.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				try {
					Test.exitCurrentAccount();
				} catch (NoException e0) {
					JOptionPane.showMessageDialog(frame, e0.getMessage() + "\n感谢您的使用");
					Test.updateUsersList();
				} catch (CardIDException e1) {
					JOptionPane.showMessageDialog(frame, e1.getMessage());
				} catch (Exception e1) {
					e1.printStackTrace();
				}
			}
		});
		right.add(exit);

		frame.add(right);
	}

	public void showScreen() {
		this.frame.setVisible(true);
	}

	public void hideScreen() {
		this.frame.setVisible(false);
	}
}
