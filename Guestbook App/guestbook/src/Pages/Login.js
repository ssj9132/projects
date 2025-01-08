import AlecLogo from '../Components/AlecLogo';
import { useNavigate } from 'react-router-dom';
import { useState } from 'react';

const Login = () => {
  const [pin, setPin] = useState('');
  const navigate = useNavigate();

  const handlePinChange = (event) => {
    setPin(event.target.value);
  };

  const handleSubmit = (event) => {
    event.preventDefault();
    if (pin === '1234') {
      navigate('/location');
    } else {
      alert('Invalid PIN! Please try again.');
    }
  };

  return (
    <div className="Login" style={{ display: 'flex', flexDirection: 'column', alignItems: 'center' }}>
      <div style={{ marginBottom: '-40px', display: 'flex', justifyContent: 'center' }}> 
        <AlecLogo />
      </div>
      <form 
        onSubmit={handleSubmit} 
        style={{
          display: 'flex',
          flexDirection: 'column',
          alignItems: 'center',
          justifyContent: 'center',
          height: '600px'
        }}
      >
        <div style={{ display: 'flex', flexDirection: 'column', alignItems: 'center', marginBottom: '20px', color: 'white' }}> 
          <label htmlFor="pin" style={{ marginBottom: '10px' }}>Enter PIN *</label>
          <input
            type="password"
            id="pin"
            value={pin}
            onChange={handlePinChange}
            maxLength={4}
            required
            style={{ padding: '10px', fontSize: '16px', borderRadius: '5px', border: '1px solid #ccc' }}
          />
        </div>
      </form>
    </div>
  );
};

export default Login;
