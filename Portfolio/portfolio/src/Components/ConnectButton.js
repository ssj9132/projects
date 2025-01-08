import '../index.css';

const CheckButton = () => {
    const handleClick = () => {
        document.getElementById('contacts').scrollIntoView({ behavior: 'smooth' });
    };

    return (
        <div className="connectbutton">
            <button onClick={handleClick}>
                Connect With Me
            </button>
        </div>
    );
};

export default CheckButton;
