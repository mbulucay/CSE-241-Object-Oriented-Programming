
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.*; 

public class Main {

	public static void main(String[] args) {
		
		final JFrame frame = new JFrame();
		JButton submit = new JButton("Submit");
		
		final ButtonGroup bg = new ButtonGroup();
		JRadioButton type1 = new JRadioButton("User vs User",true);
		JRadioButton type2 = new JRadioButton("User vs Computer");
		type1.setActionCommand("u");
		type2.setActionCommand("c");
		
		final JTextField sizeArea = new JTextField();
		
		JLabel label1 = new JLabel("Enter the size ( ex:7 ) :");
		JLabel label2 = new JLabel("Choose the type of game :");
		
		label1.setBounds(50, 20, 200, 30);
		sizeArea.setBounds(50, 50, 150, 30);
		
		label2.setBounds(50, 80, 200, 30);
		type1.setBounds(50, 110, 150, 40);
		type2.setBounds(50, 150, 150, 50);
		
		submit.setBounds(200, 200, 150, 50);
		
		submit.addActionListener(new ActionListener() {

			@Override
			public void actionPerformed(ActionEvent e) {
				try {
					HexGame hg;
					String type = bg.getSelection().getActionCommand();
					String size = sizeArea.getText();
					int s1;
					s1 = Integer.parseInt(size);
					
					if(s1 > 5) {
						if(type.equals("u")) 
							hg = new HexGame("id",s1,0,1,false,true);
						else 
							hg = new HexGame("id",s1,0,2,false,true);
					}
				}catch(Exception e1) {
					JOptionPane.showMessageDialog(frame, "You entered invalid status","warning",
						    JOptionPane.WARNING_MESSAGE);
				}
			}
		});

		bg.add(type1);
		bg.add(type2);

		frame.add(label1);
		frame.add(label2);
		frame.add(sizeArea);
		frame.add(type1);
		frame.add(type2);
		frame.add(submit);
		
		frame.setSize(400,300);
		frame.setDefaultCloseOperation(frame.EXIT_ON_CLOSE);
		frame.setLayout(null);
		frame.setVisible(true);
		
	}
}
